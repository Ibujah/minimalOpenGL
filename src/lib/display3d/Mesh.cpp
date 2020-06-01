#include <GL/glew.h>
#include "Mesh.h"

#include <glm/gtc/type_ptr.hpp>

#include <list>
#include <array>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif


Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);

	m_vboID = 0;
	m_vaoID = 0;
}

void Mesh::loadOBJ(const std::string& fileName, const std::string& texName)
{
	std::ifstream file(fileName);
	
	if(file)
	{
		std::list<glm::vec3> lver;
		std::list<glm::vec3> lnor;
		std::list<glm::vec2> ltex;

		std::list<unsigned int> lfacesV;
		std::list<unsigned int> lfacesVT;
		std::list<unsigned int> lfacesVN;

		std::string line;
		while (!file.eof())
		{
			std::getline(file, line);

			std::size_t beg;
			
			//face
			if((beg = line.find("f ")) != std::string::npos && line.find("#") == std::string::npos)
			{
				std::array<unsigned int, 3> vv;  // vertex index
				std::array<unsigned int, 3> vvt; // texture index
				std::array<unsigned int, 3> vvn; // normal index

				beg += 2;

				for(unsigned int i = 0; i < 3; i++)
				{
					unsigned int v = -1, vt = -1, vn = -1;
					std::size_t end = line.find("/", beg);
					if(end < line.length())
					{
						std::string sv = line.substr(beg, end);
						v = std::stoi(sv, nullptr);

						beg = end + 1;
						end = line.find("/", beg);
						if(beg != end)
						{
							std::string svt = line.substr(beg, end);
							vt = std::stoi(svt, nullptr);
						}
						else
							vt = v;

						beg = end + 1;
						end = line.find(" ", beg);
						if(beg != end)
						{
							std::string svn = line.substr(beg, end);
							vn = std::stoi(svn, nullptr);
						}
						else
							vn = v;
					}
					else
					{
						end = line.find(" ", beg);
						std::string sv = line.substr(beg, end);
						v = std::stoi(sv, nullptr);
					}

					vv[i] = v - 1;
					vvt[i] = vt - 1;
					vvn[i] = vn - 1;

					beg = end;
				}

				for(unsigned int i = 0; i < 3; i++)
				{
					lfacesV.push_back(vv[i]);
					lfacesVT.push_back(vvt[i]);
					lfacesVN.push_back(vvn[i]);
				}
			}
			else if( (beg = line.find("vt ")) != std::string::npos)
			{
				std::string coords = line.substr(beg + 2, line.length() - (beg + 2));
				std::istringstream iss(coords);
				double x, y;
				iss >> x >> y;

				ltex.push_back(glm::vec2(x, y));
			}
			else if((beg = line.find("vn ")) != std::string::npos)
			{
				std::string coords = line.substr(beg + 2, line.length() - (beg + 2));
				std::istringstream iss(coords);
				double x, y, z;
				iss >> x >> y >> z;

				lnor.push_back(glm::vec3(x, y, z));
			}
			else if((beg = line.find("v ")) != std::string::npos)
			{
				std::string coords = line.substr(beg + 1, line.length() - (beg + 1));
				std::istringstream iss(coords);
				double x, y, z;
				iss >> x >> y >> z;

				lver.push_back(glm::vec3(x, y, z));
			}
		}
		
		std::vector<glm::vec3> ver(lver.begin(), lver.end());
		std::vector<glm::vec3> nor(lnor.begin(), lnor.end());
		std::vector<glm::vec2> tex(ltex.begin(), ltex.end());
		
		m_vertices.resize(lfacesV.size());
		m_normals.resize(lfacesVN.size());
		m_texCoords.resize(lfacesVT.size());
		
		// faces vertices
		unsigned int indF;
		indF = 0;
		for(auto facV : lfacesV)
		{
			m_vertices[indF] = ver[facV];
			indF++;
		}

		// faces normals
		indF = 0;
		for(auto facVN : lfacesVN)
		{
			m_normals[indF] = nor[facVN];
			indF++;
		}

		// faces textures
		indF = 0;
		for(auto facVT : lfacesVT)
		{
			m_texCoords[indF] = glm::vec2(tex[facVT].x, 1.0 - tex[facVT].y);
			indF++;
		}

		m_texture = std::make_shared<Texture>(texName);

		loadBuffers();
	}
}

void Mesh::setShader(const std::shared_ptr<Shader>& shader)
{
	m_shader = shader;
}

void Mesh::display(const glm::mat4& pose, const glm::mat4& proj)
{
	if(!m_shader)
		throw std::logic_error("No shader allocated");
    glUseProgram(m_shader->getProgramID());

        glBindVertexArray(m_vaoID);
			
			glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "pose"), 1, GL_FALSE, glm::value_ptr(pose));
			glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "proj"), 1, GL_FALSE, glm::value_ptr(proj));
			
			if(m_texture)
				glBindTexture(GL_TEXTURE_2D, m_texture->getID());

			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

			glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

    glUseProgram(0);
}

void Mesh::loadBuffers()
{
	const int vertexSize = m_vertices.size()*sizeof(glm::vec3);
	const int normalSize = m_normals.size()*sizeof(glm::vec3);
	const int textureSize = m_texCoords.size()*sizeof(glm::vec2);
	
	const int vertexBeg = 0;
	const int normalBeg = vertexBeg + vertexSize;
	const int textureBeg = normalBeg + normalSize;

	GLsizeiptr sizTot = (GLsizeiptr)vertexSize + (GLsizeiptr)normalSize + (GLsizeiptr)textureSize;

	if(glIsBuffer(m_vboID) == GL_TRUE)
		glDeleteBuffers(1, &m_vboID);

    glGenBuffers(1, &m_vboID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glBufferData(GL_ARRAY_BUFFER, sizTot, 0, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, vertexBeg, vertexSize, m_vertices.data());
        glBufferSubData(GL_ARRAY_BUFFER, normalBeg, normalSize, m_normals.data());
        glBufferSubData(GL_ARRAY_BUFFER, textureBeg, textureSize, m_texCoords.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vaoID);

    glBindVertexArray(m_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexBeg));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(normalBeg));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(textureBeg));
			glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
