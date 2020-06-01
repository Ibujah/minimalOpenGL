#include <GL/glew.h>
#include "Texture.h"
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Texture::Texture(const std::string& imageFile) :
	m_id(0), 
	m_imageFile(imageFile), 
	m_width(0), 
	m_height(0), 
	m_format(0), 
	m_internalFormat(0)
{
	if(!m_imageFile.empty())
		if(!load())
			throw std::logic_error("Texture could not be loaded correctly");
}

Texture::Texture(const Texture& tex) :
	Texture(tex.m_imageFile)
{}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
	m_id = 0;
}

const Texture& Texture::operator=(const Texture& tex)
{
	if(m_id != 0)
		glDeleteTextures(1, &m_id);

	m_id = 0; 
	m_imageFile = tex.m_imageFile;
	m_width = 0;
	m_height = 0;
	m_format = 0;
	m_internalFormat = 0;
	
	if(!m_imageFile.empty())
		if(!load())
			throw std::logic_error("Texture could not be loaded correctly");
	
	return *this;
}

void Texture::setImageFile(const std::string& imageFile)
{
	m_imageFile = imageFile;
	load();
}

GLuint Texture::getID() const
{
    return m_id;
}

bool Texture::load()
{
	if(m_id != 0)
		glDeleteTextures(1, &m_id);

	cv::Mat img = cv::imread(m_imageFile.c_str(),cv::IMREAD_COLOR);
	if(!img.data)
    {
		std::cout <<  "Could not open or find the image" << std::endl ;
        return false;
    }

    glGenTextures(1, &m_id);

    glBindTexture(GL_TEXTURE_2D, m_id);

		GLenum internalFormat(GL_RGB);
		GLenum format(GL_BGR);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, img.cols, img.rows, 0, format, GL_UNSIGNED_BYTE, img.data);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}
