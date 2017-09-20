#include "GLSLProgram.hpp"

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0) {
	// Log log("GLSLProgram", "GLSLProgram", CRITICAL);
	std::cout << "GLSL constructor" << std::endl;
}

gameEngine::GLSLProgram::~GLSLProgram() {
	// Log log("GLSLProgram", "GLSLProgram", CRITICAL);
	std::cout << "GLSL destructor" << std::endl;
}

void	gameEngine::GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	// Log log("GLSLProgram", "compileShaders", CRITICAL);
	_programID = glCreateProgram();
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (_vertexShaderID == 0) {
		std::cout << "createVertexShader error" << std::endl;
		exit(EXIT_FAILURE);
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (_fragmentShaderID == 0) {
		std::cout << "createFragmentShader error" << std::endl;
		exit(EXIT_FAILURE);
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

void	gameEngine::GLSLProgram::linkShaders() {
	// Log log("GLSLProgram", "linkShaders", CRITICAL);

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if(isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		//Use the infoLog as you see fit.
		std::cout << "shader failed to link error" << std::endl;
		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
}

void	gameEngine::GLSLProgram::addAttribute(const std::string& attributeName) {
	// Log log("GLSLProgram", "addAttribute", CRITICAL);
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLint	gameEngine::GLSLProgram::getUniformLocation(const std::string& uniformName) {
	// Log log("GLSLProgram", "getUniformLocation", CRITICAL);
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		std::cout << "invalid uniform name in shader" << std::endl;
		exit(EXIT_FAILURE);
	}
	return location;
}

void	gameEngine::GLSLProgram::use() {
	// Log log("GLSLProgram", "use", CRITICAL);
	// glUseProgram(_programID);
	// GLint posAttrib = glGetAttribLocation(_programID, "vertexPosition");
	// glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(posAttrib);
	//enable the shader, and all its attributes

	glUseProgram(_programID);
	//enable all the attributes we added with addAttribute
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}


void	gameEngine::GLSLProgram::unUse() {
	// Log log("GLSLProgram", "unUse", CRITICAL);
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void	gameEngine::GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
	// Log log("GLSLProgram", "compileShader", CRITICAL);
	std::ifstream shaderFile(filePath);

	if (shaderFile.fail()) {
		std::cout << "failed to open " << filePath << std::endl;
	}
	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line)) {
		fileContents += line + '\n';
	}
	shaderFile.close();

	const char * contentsPtr = fileContents.c_str();

	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(id);

		std::printf("%s\n", &errorLog[0]);
		std::cout << "Shader " << filePath << " failed to compile" << std::endl;
	}
}