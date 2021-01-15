#pragma once
#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

///Include Glew Functions, etc.
#include <GL/glew.h>
///Include Basic std::... Fucntions
#include <iostream>


//This class Fills in the VertexShader's outline of each Model
class FragmentShader
{
///Private Class Variables
private:
	//Shader creates a Textured Ambient Lighted Model Face
	const GLchar* ambientOnlyFSSrc =
		"uniform vec4 u_Color;		"\
		"							"\
		"void main()				"\
		"{							"\
		"	gl_FragColor = u_Color;	"\
		"}							";

	//Shader creates an Bright Ambient Lighted Model Face
	const GLchar* textureAmbientFSSrc =
		"uniform sampler2D u_Texture;"\
		"							"\
		"varying vec2 v_TexCoord;	"\
		"varying vec3 v_Normal;		"\
		"varying vec3 v_FragPos;	"\
		"							"\
		"uniform vec3 u_Ambient;	"\
		"							"\
		"void main()				"\
		"{							"\
		"	vec4 col = texture2D(u_Texture, v_TexCoord);"\
		"	gl_FragColor = col * vec4(u_Ambient, 1);	"\
		"}							";

	//Shader creates a Textured Directional Lighted Model Face
	const GLchar* textureLightedFSSrc =
		"uniform sampler2D u_Texture;"\
		"							"\
		"varying vec2 v_TexCoord;	"\
		"varying vec3 v_Normal;		"\
		"varying vec3 v_FragPos;	"\
		"							"\
		"uniform vec3 u_Ambient;	"\
		"							"\
		"void main()				"\
		"{							"\
		"	vec3 norm = normalize(v_Normal);						"\
		"	vec3 lightDir = normalize(vec3(0, 640, -20) - v_FragPos);"\
		"	float diff = max(dot(norm, lightDir), 0.0f);			"\
		"	vec3 diffuse = vec3(1, 1, 1) * diff;					"\
		"	vec3 lighting = min(diffuse + u_Ambient, vec3(1, 1, 1));"\
		"							"\
		"	vec4 col = texture2D(u_Texture, v_TexCoord);			"\
		"	gl_FragColor = col * vec4(lighting, 1);					"\
		"}							";

	//The ID of THIS Fragment Shader
	GLuint vaoID = 0;
	//Used to see if THIS Fragment Shader is Created Successfully, or NOT
	GLint fSuccess = 0;

///Public Class Functions
public:
	//Constructor
	FragmentShader();
	//Deconstructor
	~FragmentShader();


	//Create a New Vertex Shader for the Model's Shader Program
	bool createFragmentShader(int shaderChoice);


	//Return the ID of THIS FragmentShader
	GLuint getID();
};

#endif