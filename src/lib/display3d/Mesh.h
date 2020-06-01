#ifndef DEF_MESH
#define DEF_MESH

#if defined(_WIN32)
#include <Windows.h>
#elif defined(_WIN64)
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Shader.h"
#include "Texture.h"

/**
 *  \brief Mesh class
 */
class Mesh
{
	protected:
		/// Shader used
		std::shared_ptr<Shader> m_shader{};

		/// Texture used
		std::shared_ptr<Texture> m_texture{};
		
		/// Set of vertices
		std::vector<glm::vec3> m_vertices{0};
		/// Set of normals
		std::vector<glm::vec3> m_normals{0};
		/// Set of texture coordinates
		std::vector<glm::vec2> m_texCoords{0};
		
		/// Vertex Buffer Object identifier
		GLuint m_vboID{0};
		/// Vertex Array Object identifier
		GLuint m_vaoID{0};

    public:
		/**
		 *  \brief Destructor of the mesh
		 */
		~Mesh();
		
		/**
		 *  \brief Loads an obj file
		 *  \param fileName  Name of the obj file
		 *  \param texName   Name of the texture file
		 */
		void loadOBJ(const std::string& fileName, const std::string& texName = "");
		
		/**
		 *  \brief Set a shader to the mesh
		 *  \param shader  Shader to set
		 */
		void setShader(const std::shared_ptr<Shader>& shader);
		
		/**
		 *  \brief Display mesh
		 *  \param pose  Pose matrix of the camera
		 *  \param proj  Projection matrix of the camera
		 */
		void display(const glm::mat4& pose, const glm::mat4& proj);

	protected:
		/**
		 *  \brief Loads the vertex buffers when vertices, normals and texture coordinates are set
		 */
		void loadBuffers();
};

#endif
