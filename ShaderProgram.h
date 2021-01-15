#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

///Includes Base GLM Functions, Data Types, etc.
#include <\myengine\contrib\glm/glm.hpp>

///Allows std::shared_ptr
#include <memory>

///Includes Access to Creation of Vertex Shader
#include "myengine/VertexShader.h"
class VertexShader;
///Includes Access to Creation of Fragment Shader
#include "myengine/FragmentShader.h"
class FragmentShader;


//This Class creates a Vertex and Fragment Shader to THIS Model
class ShaderProgram
{
///Private Class Variables
private:
	//Shared Pointer to the ShaderPorgram's VertexShader
	std::shared_ptr<VertexShader> vertexShader;
	//Shared Pointer to the ShaderProgram's VertexShader
	std::shared_ptr<FragmentShader> fragmentShader;

	//The ID to access THIS program
	GLuint vaoID = 0;
	//Used to check if THIS Model's Shader Program is
	//Compiled successfully or not
	GLint pSuccess = 0;

///Public Class Functions
public:
	//Constructor
	ShaderProgram();
	//Deconstructor
	~ShaderProgram();


	//Creates a NEW Shader Program, for THIS Model
	//Using a NEW Vertex and Fragment Shader
	bool newShaderProgram(int shaderChoice);


	//Returns the ID of THIS ShaderProgram
	GLuint getID();
};

#endif