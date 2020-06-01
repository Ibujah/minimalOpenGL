#ifndef DEF_CAMERA
#define DEF_CAMERA

#if defined(_WIN32)
#include <Windows.h>
#elif defined(_WIN64)
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <glm/glm.hpp>

/**
 *  \brief Camera class
 */
class Camera
{
	protected:
		/// Width of the image
		unsigned int m_width;
		/// Height of the image
		unsigned int m_height;
		
		/// X coordinate of principal point
		double m_cx;      
		/// Y coordinate of principal point
		double m_cy;
		/// X focal
		double m_fx;
		/// Y focal
		double m_fy;
		
		/// Near clipping distance
		double m_zNear;
		/// Far clipping distance
		double m_zFar;
		
		/// Projection matrix
		glm::mat4 m_projectionMat;
		/// Transformation matrix
		glm::mat4 m_transformationMat;
	
    public:
		/**
		 *  \brief Constructor
		 *  \param width   Width of the image
		 *  \param height  Height of the image
		 *  \param zNear   Near clipping distance
		 *  \param zFar    Far clipping distance
		 *  \details  Chooses automatically the principal point and the focal
		 */
		Camera(unsigned int width = 600, 
			   unsigned int height = 400,
			   double zNear = 0.1,
			   double zFar = 100.0);

		/**
		 *  \brief Constructor
		 *  \param width   Width of the image
		 *  \param height  Height of the image
		 *  \param cx      X coordinate of principal point
		 *  \param cy      Y coordinate of principal point
		 *  \param fx      X focal
		 *  \param fx      Y focal
		 *  \param zNear   Near clipping distance
		 *  \param zFar    Far clipping distance
		 */
		Camera(unsigned int width, 
			   unsigned int height,
			   double cx,
			   double cy,
			   double fx,
			   double fy,
			   double zNear = 0.1,
			   double zFar = 100.0);

		/**
		 *  \brief Set the intrinsics of the camera
		 *  \param width   Width of the image
		 *  \param height  Height of the image
		 *  \param zNear   Near clipping distance
		 *  \param zFar    Far clipping distance
		 *  \details  Chooses automatically the principal point and the focal
		 */
		void setIntrinsics(unsigned int width, 
						   unsigned int height);

		/**
		 *  \brief Set the intrinsics of the camera
		 *  \param width   Width of the image
		 *  \param height  Height of the image
		 *  \param cx      X coordinate of principal point
		 *  \param cy      Y coordinate of principal point
		 *  \param fx      X focal
		 *  \param fx      Y focal
		 *  \param zNear   Near clipping distance
		 *  \param zFar    Far clipping distance
		 */
		void setIntrinsics(unsigned int width, 
						   unsigned int height,
						   double cx,
						   double cy,
						   double fx,
						   double fy);
		
		/**
		 *  \brief Set the extrinsics of the camera
		 *  \param transformationMat  New extrinsics of the camera
		 */
		void setExtrinsics(const glm::mat4& transformationMat = glm::mat4(1.0));
		
		/**
		 *  \brief Set the position of the camera
		 *  \param vec  New position of the camera
		 */
		void setPosition(const glm::vec3& vec = glm::vec3(0.0, 0.0, 0.0));
		
		/**
		 *  \brief Translate the camera
		 *  \param vec  Translation to apply
		 */
		void translate(const glm::vec3& vec);

		/**
		 *  \brief Rotate the camera
		 *  \param angle  Rotation angle (radian)
		 *  \param vec    Rotation axis
		 */
		void rotate(float angle, const glm::vec3& vec);
		
		/**
		 *  \brief Width getter
		 *  \return Width of the image
		 */
		const unsigned int getWidth() const;

		/**
		 *  \brief Height getter
		 *  \return Height of the image
		 */
		const unsigned int getHeight() const;

		/**
		 *  \brief Intrinsics getter
		 *  \return Intrinsics of the camera
		 */
		const glm::mat4& getIntrinsics() const;

		/**
		 *  \brief Extrinsics getter
		 *  \return Extrinsics of the camera
		 */
		const glm::mat4& getExtrinsics() const;

	protected:
		/**
		 *  \brief Computes the intrinsics of the camera from the principal point, the focals and the size of the image
		 */
		void computeIntrinsics();
};

#endif

