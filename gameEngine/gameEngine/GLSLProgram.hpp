#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl3.h>

namespace gameEngine {
	class GLSLProgram {

    	public:
        	GLSLProgram();
        	~GLSLProgram();

        	void    compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        	void    linkShaders();
        	void    addAttribute(const std::string& attributeName);

        	GLint   getUniformLocation(const std::string& uniformName);

        	void    use();
        	void    unUse();
    
    	private:

        	void    compileShader(const std::string& filePath, GLuint id);
        
        	GLuint  _programID;
        	GLuint  _vertexShaderID;
        	GLuint  _fragmentShaderID;
        	int     _numAttributes;
	};
}
