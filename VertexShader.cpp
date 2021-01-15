#include "VertexShader.h"


//Constructor
VertexShader::VertexShader()
{ }

//Deconstructor
VertexShader::~VertexShader()
{ }


//Create a New Vertex Shader for the Model's Shader Program
bool VertexShader::createVertexShader(int shaderType)
{
	///Create a NEW Vertex Shader id
	vaoID = glCreateShader(GL_VERTEX_SHADER);
	///Depending on pass by value
	switch (shaderType)
	{
		///If the shaderChoice is '0'
	case 0:
		///Use the ambientOnlyVSSrc as the Code for THIS Vertex Shader
		glShaderSource(vaoID, 1, &ambientOnlyVSSrc, NULL);
		break;
		///If the shaderChoice is '1'
	case 1:
		///Use the textureAmbientVSSrc as the Code for THIS Vertex Shader
		glShaderSource(vaoID, 1, &textureAmbientVSSrc, NULL);
		break;
		///If the shaderChoice is '2'
	case 2:
		///Use the textureLightedVSSrc as the Code for THIS Vertex Shader
		glShaderSource(vaoID, 1, &textureLightedVSSrc, NULL);
		break;
		///If any other value, return as an error
	default:
		std::cout << "\n\nERROR: Out of bounds choosing correct Vertex Shader";
		return false;
		break;
	}
	///Run the Source Code selected from 
	glCompileShader(vaoID);

	///Get the status of the 'glCompileShader(vaoID);'
	glGetShaderiv(vaoID, GL_COMPILE_STATUS, &vSuccess);
	///If compile was successful, return without error
	if (vSuccess)
	{
		//std::cout << "\nEVENT: Compiled Vertex Shader";
		return true;
	}
	///If failure, return as an error
	else
	{
		std::cout << "\n\nERROR Compiling Vertex Shader";
		return false;
	}

	///Defaultly return as an error
	return false;
}


//If the ID exists, return it
GLuint VertexShader::getID()
{
	///If there is a ID created for THIS Vertex Shader then return it
	if (vaoID)
	{
		return vaoID;
	}
	///If there is NO Created Vertex Shader, then return as an error
	std::cout << "\n\nERROR: Getting Vertex Shader ID";
	return 0;
}