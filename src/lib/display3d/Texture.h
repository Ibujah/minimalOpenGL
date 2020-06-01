#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#if defined(_WIN32)
#include <Windows.h>
#elif defined(_WIN64)
#include <Windows.h>
#endif

#include <string>
#include <GL/gl.h>

/**
 *  \brief Texture class
 */
class Texture
{
	protected:
		/// Texture identifier
		GLuint m_id;
		/// Image file
		std::string m_imageFile;
		
		/// Texture width
		int m_width;
		/// Texture height
		int m_height;
		
		/// Texture format
		GLenum m_format;
		/// Texture internal format
		GLenum m_internalFormat;

	public:
		/**
		 *  \brief Constructor
		 *  \param imageFile  Image file
		 */
		Texture(const std::string& imageFile = "");

		/**
		 *  \brief Copy constructor
		 *  \param tex Texture to copy
		 */
		Texture(const Texture& tex);
		
		/**
		 *  \brief Destructor
		 */
		~Texture();

		/**
		 *  \brief Assignment operator
		 *  \param tex  Texture to copy
		 *  \return Reference to current texture
		 */
		const Texture& operator=(const Texture& tex);
		
		/**
		 *  \brief Texture identifier getter
		 */
		GLuint getID() const;
		
		/**
		 *  \brief Set or changes the texture image
		 *  \param imageFile  New image file
		 */
		void setImageFile(const std::string& imageFile);

	protected:
		/**
		 *  \brief Loads the texture
		 *  \return True if loaded correctly
		 */
		bool load();
};

#endif
