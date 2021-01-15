#include "FragmentShader.h"


//Constructor
FragmentShader::FragmentShader()
{ }

//Deconstructor
FragmentShader::~FragmentShader()
{ }


//Create a New Fragment Shader for the Model's Shader Program
bool FragmentShader::createFragmentShader(int shaderChoice)
{
	///Create a NEW Fragment Shader id
	vaoID = glCreateShader(GL_FRAGMENT_SHADER);
	///Depending on pass by value
	switch (shaderChoice)
	{
		///If the shaderChoice is '0'
	case 0:
		///Use the ambientOnlyFSSrc as the Code for THIS Fragment Shader
		glShaderSource(vaoID, 1, &ambientOnlyFSSrc, NULL);
		break;
		///If the shaderChoice is '1'
	case 1:
		///Use the textureAmbientFSSrc as Code for THIS Fragment Shader
		glShaderSource(vaoID, 1, &textureAmbientFSSrc, NULL);
		break;
		///If the shaderChoice is '2'
	case 2:
		///Uuse the textureLightedFSSrc as Code for THIS Fragment Shader
		glShaderSource(vaoID, 1, &textureLightedFSSrc, NULL);
		break;
		///If any other value, return as an error
	default:
		std::cout << "\n\nERROR: Out of bounds choosing correct Fragment Shader";
		break;
	}
	///Run the Source Code selected from 
	glCompileShader(vaoID);

	///Get the status of the 'glCompileShader(vaoID);'
	glGetShaderiv(vaoID, GL_COMPILE_STATUS, &fSuccess);
	///If compile was successful, return without error
	if (fSuccess)
	{
		//std::cout << "\nEVENT: Compiled Fragment Shader";
		return true;
	}
	///If failure, return as an error
	else
	{
		std::cout << "\n\nERROR Compiling Fragment Shader";
		return false;
	}
}


//If the ID exists, return it
GLuint FragmentShader::getID()
{
	///If there is a ID created for THIS Fragment Shader then return it
	if (vaoID)
	{
		return vaoID;
	}
	///If there is NO Created Fragment Shader, then return as an error
	std::cout << "\n\nERROR: Getting Fragment Shader ID";
	return 0;
}