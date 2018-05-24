
#include "shader.h"
#include <iostream>
#include "vertex.h"

Shader::Shader(std::string vertexCode, std::string fragmentCode) 
{
	int retCode;
	error = "";
	vertexShaderSource = vertexCode;
	fragmentShaderSource = fragmentCode;
	
	const char* cVertexShaderSource = vertexShaderSource.c_str();
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &cVertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		char errorLog[1024];
		glGetShaderInfoLog(vertexShader, sizeof(errorLog), nullptr, errorLog);
		glDeleteShader(vertexShader);
		//set error
		error = error + "vertex shader could not be compiled:" + errorLog;
	}

	// create fragment shader
	const char* cFragmentShaderSource = fragmentShaderSource.c_str();
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &cFragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		char errorLog[1024];
		glGetShaderInfoLog(fragmentShader, sizeof(errorLog), nullptr, errorLog);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		error = error + "fragment shader could not be compiled:" +  errorLog;
	}

	// create and link program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(program, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		char errorLog[1024];
		glGetProgramInfoLog(program, sizeof(errorLog), nullptr, errorLog);
		glDeleteProgram(program);
		error = error + "program could not be linked:" + errorLog;
	}

	// use program and get locations
	vPosLoc = glGetAttribLocation(program, "vpos");
	vColorLoc = glGetAttribLocation(program, "vcolor");
}

void Shader::setupAttribs() const 
{
	if (vPosLoc != -1) {
		glEnableVertexAttribArray(vPosLoc);
		glVertexAttribPointer(vPosLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, pos.x)));

	}
	if (vColorLoc != -1) {
		glEnableVertexAttribArray(vColorLoc);
		glVertexAttribPointer(vColorLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, color.r)));

	}
		
}

Shader::~Shader() 
{
	glDeleteProgram(program);
}