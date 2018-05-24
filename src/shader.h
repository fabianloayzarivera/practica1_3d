#pragma once
#include "common.h"

class Shader 
{
private:
	uint32_t program;
	std::string error;
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	int vPosLoc;
	int vColorLoc;
	glm::mat4 mvp;

public:

	Shader(std::string vertexCode, std::string fragmentCode);
	~Shader();

	// Devuelve el identificador de OpenGL del programa
	uint32_t	getId() const { return program; }

	// Obtiene el mensaje de error generado al compilar o enlazar
	std::string	getError() const { return error; }

	// Activa el uso de este programa
	void		use() const { glUseProgram(program); }

	// Activa la escritura de las variables attribute,
	// y especifica su formato
	void		setupAttribs() const;

	// Obtiene la localización de una variable uniform
	int		getLocation(const char* name) const { return glGetUniformLocation(program, name); }

	// Da valor a una variable uniform
	void		setInt(int loc, int val) { if(loc != -1) glUniform1i(loc, val); }
	void		setFloat(int loc, float val) { if (loc != -1) glUniform1f(loc, val); }
	void		setVec3(int loc, const glm::vec3& vec) { if (loc != -1) glUniform3f(loc, vec.x, vec.y, vec.z); }
	void		setVec4(int loc, const glm::vec4& vec) { if (loc != -1) glUniform4f(loc, vec.x, vec.y, vec.z, vec.w); }
	void		setMatrix(int loc, const glm::mat4& matrix) { if(loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix)); }

};


template < typename T > class SP
{
private:
	T * pData;
public:
	SP(T* pValue) : pData(pValue)
	{
	}
	~SP()
	{
		delete pData;
	}

	T& operator* ()
	{
		return *pData;
	}

	T* operator-> ()
	{
		return pData;
	}
};