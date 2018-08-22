//---------------------------------------------------------
// Code adapted from https://learnopengl.com
//

#pragma once
#ifndef SHADER_H
#define SHADER_H

// includes
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	unsigned int ID;
	
	//------------------------------------------------
	// constructor to read file and build the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		//----------------------------
		// retrieve shader source code
		string vertexCode, fragmentCode;
		ifstream vsFile, fsFile;

		vsFile.open(vertexPath);
		fsFile.open(fragmentPath);
		stringstream vsstream, fsstream;

		vsstream << vsFile.rdbuf();
		fsstream << fsFile.rdbuf();

		vsFile.close();
		fsFile.close();

		vertexCode = vsstream.str();
		fragmentCode = fsstream.str();

		const char* vsCode = vertexCode.c_str();
		const char* fsCode = fragmentCode.c_str();

		//----------------------------
		// Compile shaders from source
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vsCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fsCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// create a shader program
		ID = glCreateProgram();

		// attach shaders
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	//-------------------------
	// activate the shader
	void use()
	{
		glUseProgram(ID);
	}

	//---------------------------------
	// utility functions
	void setBool(const string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
};

#endif