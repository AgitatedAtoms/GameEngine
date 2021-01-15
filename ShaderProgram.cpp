///Includes access to ShaderProgram's Class Header File
#include "ShaderProgram.h"


//Constructor
ShaderProgram::ShaderProgram()
{ }

//Deconstructor
ShaderProgram::~ShaderProgram()
{ }


//Creates a NEW Shader Program, for THIS Model
//Using a NEW Vertex and Fragment Shader
bool ShaderProgram::newShaderProgram(int shaderType)
{
	///Reset the Previous Vertex Shader, ready for a new one
	vertexShader.reset();
	///Create a new Vertex Shader
	vertexShader = std::make_shared<VertexShader>();
	vertexShader->createVertexShader(shaderType);

	///Reset the Previous Fragment Shader, ready for a new one
	fragmentShader.reset();
	///Create a new Fragment Shader
	fragmentShader = std::make_shared<FragmentShader>();
	fragmentShader->createFragmentShader(shaderType);


	///-----------------Attach Shaders to Program-----------------///
	///Create a New Shader Program an assign to new ID
	vaoID = glCreateProgram();

	///Attaach Both Vertex and Fragment Shaders to THIS shader program
	glAttachShader(vaoID, vertexShader->getID());
	glAttachShader(vaoID, fragmentShader->getID());
	
	///Inside the Shader's source code, bind "a_Position"
	glBindAttribLocation(vaoID, 0, "a_Position");
	
	///If the shaderChoice is 2/0, bind "a_TexCoord"
	///Allows for Textured Models to be Renderer
	if (shaderType == 1 ||
		shaderType == 2)
	{
		glBindAttribLocation(vaoID, 1, "a_TexCoord");
	}
	//std::cout << "\nEVENT: Created Shader Program";


	///-----------------Link Program-----------------///
	///If there is an error creating a new Shader Program
	///Return as an error
	if (!vaoID)
	{
		return false;
	}

	///Link THIS ShaderProgram to use on Model
	glLinkProgram(vaoID);
	///Run the source code for Shaders and see if successful
	glGetProgramiv(vaoID, GL_LINK_STATUS, &pSuccess);
	///If Shaders Successfully compiled, continue
	if (pSuccess)
	{
		//std::cout << "\nEVENT: Linked Program";
	}
	///If Compiling Failure, then return as an error
	else
	{
		std::cout << "\n\nERROR: Linking Program";
		return false;
	}


	///Change Colour Shade
	///For glReadPixels
	///ONLY if object uses the basic shader
	if (shaderType == 0)
	{
		///Get the Location of the Uniform Variable "u_Color"
		///inside the shaders
		GLint loc = glGetUniformLocation(vaoID, "u_Color");
		
		///If found the location of "u_Color"
		if (loc != -1)
		{
			///Set THIS Location
			///u_Color = glm::vec4(0.03f, 0.03f, 0.03f, 1.0f)
			glUniform4f(loc, 0.03f, 0.03f, 0.03f, 1.0f);
			glUseProgram(0);
		}
		///If not found location of "u_Color"
		///Return as an error
		else
		{
			std::cout << "\n\nERROR: Cannot find 'u_Color' in Shaders";
			return false;
		}
	}

	///Chande the ambient lighting of the object
	///Change 'u_Ambient' uniform vec3 in fragment shader
	if (shaderType == 1 ||
		shaderType == 2)
	{
		///Find the Location of Uniform Variable "u_Ambient"
		GLint loc = glGetUniformLocation(vaoID, "u_Ambient");
		
		///If location of "u_Ambient" found,
		if (loc != -1)
		{
			glUseProgram(vaoID);
			glm::vec3 ambient{ 0.0f, 0.0f, 0.0f };
			///Depending on pass by value
			switch (shaderType)
			{
				///If shaderChoice == '0'
			case 1:
				///Set ambient light to VERY bright
				ambient = glm::vec3{ 1.0f, 1.0f, 1.0f };
				break;
				///If shaderChoice == '2'
			case 2:
				///Set ambient light to dull brightness
				ambient = glm::vec3{ 0.3f, 0.3f, 0.3f };
				break;
				///If shaderChoice != '0' OR '2'
				///Return as an error
			default:
				std::cout << "\n\nERROR: Incorrect 'shaderChoice == " << shaderType;
				return false;
				break;
			}
			glUniform3f(loc, ambient.x, ambient.y, ambient.z);
			glUseProgram(0);

			//std::cout << "\nEVENT: Changed 'u_Ambient' to: "
			//	<< ambient.x << ", " << ambient.y << ", " << ambient.z
			//	<< " in Shader";
		}
		///If "u_Ambient" not found in shaders
		///Return as an error
		else
		{
			std::cout << "\n\nERROR: Cannot find 'u_Ambient' in Shaders";
			return false;
		}
	}


	///-----------------Clean Shaders-----------------///
	///Vertex and Fragment Shader is Created Successfuly,
	
	///Detach Vertex Shader then Delete
	glDetachShader(vaoID, vertexShader->getID());
	glDetachShader(vaoID, fragmentShader->getID());

	///Detach Fragment Shader then Delete
	glDeleteShader(vertexShader->getID());
	glDeleteShader(fragmentShader->getID());

	///Return as Function completed Successfully
	return true;
}


//Returns the ID of THIS ShaderProgram
GLuint ShaderProgram::getID()
{
	///If there is a shaderProgram ID created, then return it
	if (vaoID)
	{
		return vaoID;
	}
	///IF there is NO shaderProgram ID created,
	///then return as an error
	std::cout << "\n\nERROR: Getting ShaderProgram ID";
	return 0;
}