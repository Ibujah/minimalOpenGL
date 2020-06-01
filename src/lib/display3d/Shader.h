#ifndef DEF_SHADER
#define DEF_SHADER

#if defined(_WIN32)
#include <Windows.h>
#elif defined(_WIN64)
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <string>

/**
 *  \brief Shader class
 */ 
class Shader
{
	protected:
		/// Vertex shader identifier
		GLuint m_vertexID;
		/// Fragment shader identifier
		GLuint m_fragmentID;
		/// Shader program identifier
		GLuint m_programID;
		
		/// Vertex source file
		std::string m_vertexSource;
		/// Fragment source file
		std::string m_fragmentSource;

    public:
		/**
		 *  \brief Constructor
		 *  \param vertexSource    Filename for vertex shader
		 *  \param fragmentSource  Filename for fragment shader
		 */
		Shader(std::string const vertexSource = "", std::string const fragmentSource = "");
		
		/**
		 *  \brief Copy constructor
		 *  \param shad  Shader to copy
		 */
		Shader(const Shader& shad);
		
		/**
		 *  \brief Destructor
		 */
		~Shader();
		
		/**
		 *  \brief Assignment operator
		 *  \param shad  Shader to copy
		 *  \return Reference to current shader
		 */
		const Shader& operator=(const Shader& shad);

		/**
		 *  \brief Set shader sources
		 *  \param vertexSource    Filename for vertex shader
		 *  \param fragmentSource  Filename for fragment shader
		 */
		void setSources(std::string const vertexSource = "", std::string const fragmentSource = "");

		/**
		 *  \brief Program shader identifier getter
		 *  \return Program shader identifier
		 */
		GLuint getProgramID() const;

	protected:
		/**
		 *  \brief Loads the shaders
		 *  \return True if loaded correctly
		 */
		bool load();
		
		/**
		 *  \brief Compile a given shader source
		 *  \param [out] shader  Shader identifier
		 *  \param type          Shader type (fragment or vertex)
		 *  \param sourceFile    Shader source file
		 *  \return True if the shader was correctly loaded
		 */
		static bool compileShader(GLuint &shader, const GLenum type, const std::string& sourceFile);
};

#endif
