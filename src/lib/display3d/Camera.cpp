#include "Camera.h"
//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(unsigned int width, 
			   unsigned int height,
			   double zNear,
			   double zFar) :
	Camera(width,
		   height,
		   (double)width/2.0,
		   (double)height/2.0,
		   (double)(width + height)/2.0,
		   (double)(width + height)/2.0,
		   zNear,
		   zFar)
{}

Camera::Camera(unsigned int width, 
			   unsigned int height,
			   double cx,
			   double cy,
			   double fx,
			   double fy,
			   double zNear,
			   double zFar) :
		m_transformationMat(1.0),
		m_zNear(zNear),
		m_zFar(zFar)
{
	setIntrinsics(width, height, cx, cy, fx, fy);
}

void Camera::setIntrinsics(unsigned int width, 
						   unsigned int height)
{
	m_width = width;
	m_height = height;
	m_cx = (double)width/2.0;
	m_cy = (double)height/2.0;
	m_fx = (double)(width + height)/2.0;
	m_fy = (double)(width + height)/2.0;

	computeIntrinsics();
}

void Camera::setIntrinsics(unsigned int width, 
						   unsigned int height,
						   double cx,
						   double cy,
						   double fx,
						   double fy)
{
	m_width = width;
	m_height = height;
	m_cx = cx;
	m_cy = cy;
	m_fx = fx;
	m_fy = fy;

	computeIntrinsics();
}

void Camera::setExtrinsics(const glm::mat4& transformationMat)
{
	m_transformationMat = transformationMat;
}

void Camera::setPosition(const glm::vec3& vec)
{
	m_transformationMat[3][0] = vec.x;
	m_transformationMat[3][1] = vec.y;
	m_transformationMat[3][2] = vec.z;
	m_transformationMat[3][3] = 1.0;
}

void Camera::translate(const glm::vec3& vec)
{
	m_transformationMat = glm::translate(m_transformationMat, vec);
}

void Camera::rotate(float angle, const glm::vec3& vec)
{
	m_transformationMat = glm::rotate(m_transformationMat, angle, vec);
}

const unsigned int Camera::getWidth() const
{
	return m_width;
}

const unsigned int Camera::getHeight() const
{
	return m_height;
}

const glm::mat4& Camera::getIntrinsics() const
{
	return m_projectionMat;
}

const glm::mat4& Camera::getExtrinsics() const
{
	return m_transformationMat;
}

void Camera::computeIntrinsics()
{
	m_projectionMat[0][0] = 2.0*m_fx/(double)m_width;
	m_projectionMat[0][1] = 0.0;
	m_projectionMat[0][2] = 0.0;
	m_projectionMat[0][3] = 0.0;

	m_projectionMat[1][0] = 0.0;
	m_projectionMat[1][1] = -2.0*m_fy/(double)m_height;
	m_projectionMat[1][2] = 0.0;
	m_projectionMat[1][3] = 0.0;

	m_projectionMat[2][0] = (2.0*m_cx/(double)m_width - 1.0);
	m_projectionMat[2][1] = -(2.0*m_cy/(double)m_height - 1.0);
	m_projectionMat[2][2] = (m_zFar + m_zNear) / (m_zFar - m_zNear);
	m_projectionMat[2][3] = 1.0;

	m_projectionMat[3][0] =  0.0;
	m_projectionMat[3][1] =  0.0;
	m_projectionMat[3][2] = -2.0 * m_zFar * m_zNear/(m_zFar-m_zNear);
	m_projectionMat[3][3] =  0.0;
}
