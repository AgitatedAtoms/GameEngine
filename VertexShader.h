#pragma once
#ifndef VAO_H
#define VAO_H

///Includes Glew Functions, etc
#include <GL/glew.h>

///Include Base C++ functions: std::..cout/cin/etc
#include <iostream>


//This Class is used to Find the Model's Edges
class VertexShader
{
private:
	//Shader creates an Bright Ambient Lighted Edge
	const GLchar* ambientOnlyVSSrc =
		"attribute vec3 a_Position;	"\
		"							"\
		"uniform vec4 u_Color;		"\
		"							"\
		"uniform mat4 u_Projection;	"\
		"uniform mat4 u_Model;		"\
		"							"\
		"void main()				"\
		"{							"\
		"	gl_Position = u_Projection * u_Model * vec4(a_Position, 1);"\
		"}							";

	//Shader creates a Textured Ambient Lighted Edge
	const GLchar* textureAmbientVSSrc =
		"attribute vec3 a_Position;	"\
		"attribute vec2 a_TexCoord;	"\
		"							"\
		"uniform mat4 u_Projection;	"\
		"uniform mat4 u_Model;		"\
		"							"\
		"varying vec2 v_TexCoord;	"\
		"varying vec3 v_FragPos;	"\
		"							"\
		"void main()				"\
		"{							"\
		"	v_FragPos = vec3(u_Model * vec4(a_Position, 1));"\
		"	v_TexCoord = a_TexCoord;"\
		"	gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0);"\
		"}							";
	
	//Shader creates a Textured Directional Lighted Edge
	const GLchar* textureLightedVSSrc =
		"attribute vec3 a_Position;	"\
		"attribute vec2 a_TexCoord;	"\
		"attribute vec3 a_Normal;	"\
		"							"\
		"uniform mat4 u_Projection;	"\
		"uniform mat4 u_Model;		"\
		"							"\
		"varying vec2 v_TexCoord;	"\
		"varying vec3 v_Normal;		"\
		"varying vec3 v_FragPos;	"\
		"							"\
		"void main()				"\
		"{							"\
		"	v_Normal = a_Normal;	"\
		"	v_FragPos = vec3(u_Model * vec4(a_Position, 1));"\
		"	v_TexCoord = a_TexCoord;"\
		"	gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0);"\
		"}							";

	//The ID of THIS Vertex Shader
	GLuint vaoID = 0;
	//Used to see if THIS Vertex Shader is Created Successfully or NOT
	GLint vSuccess = 0;

public:
	//Constructor
	VertexShader();
	//Deconstructor
	~VertexShader();


	//Create a New Vertex Shader for the Model's Shader Program
	bool createVertexShader(int shaderChoice);


	//If the ID exists, return it
	GLuint getID();
};

#endif