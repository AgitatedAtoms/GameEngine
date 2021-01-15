///Includes access to Model's Header File
#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//Constructor
Model::Model()
{
	data = Data();

	data.modelDir = "";
	data.textureDir = "";

	data.defaultTransform.position = glm::vec3{ 0.0f, 0.0f, 0.0f };
	data.defaultTransform.rotation = glm::vec3{ 0.0f, 0.0f, 0.0f };
	data.defaultTransform.scale = glm::vec3{ 2.0f, 2.0f, 2.0f };

	data.currentTransform = data.defaultTransform;

	data.shaderType = 0;
	data.drawType = 0;
}

//Deconstructor
Model::~Model()
{ }


//Creates a new model using pass by Default Transformation, Model and Texture Directories
void Model::newModel(Data _modelData)
{
	data.modelDir = _modelData.modelDir;
	data.textureDir = _modelData.textureDir;

	data.defaultTransform = _modelData.defaultTransform;
	data.currentTransform = _modelData.currentTransform;

	data.shaderType = _modelData.shaderType;
	data.drawType = _modelData.drawType;

	///Create Model's glm::mat4 matrix
	updateModelMatrix();

	///Create Model and Texture
	if (data.modelDir != "")
	{
		loadModel(data.modelDir);
	}
	if (data.textureDir != "")
	{
		loadTexture(data.textureDir);
	}
}


//Reset THIS Model's Transform to its Default Values
void Model::resetModel()
{
	///Reset Values to Default Values
	data.currentTransform.position = data.defaultTransform.position;
	data.currentTransform.rotation = data.defaultTransform.rotation;
	data.currentTransform.scale = data.defaultTransform.scale;

	///Create new Model Transformation Matrix
	updateModelMatrix();

	//std::cout << "\nEVENT: Reset Model";
}


///------------------Current Transformation------------------///
//Updates the Current Model's Position to the newPosition values
void Model::updatePosition(glm::vec3 newPosition)
{
	data.currentTransform.position = newPosition;
	updateModelMatrix();
}
//Updates the Current Model's Rotation to the newRotation values
void Model::updateRotation(glm::vec3 newRotation)
{
	data.currentTransform.rotation = newRotation;
	updateModelMatrix();
}
//Updates the Current Model's Scale to the newScale values
void Model::updateScale(glm::vec3 newScale)
{
	data.currentTransform.scale = newScale;
	updateModelMatrix();
}
//Updates the Current Model's Transformation Matrix
void Model::updateModelMatrix()
{
	///Create a identity Matrix to add the Model's Transformations onto
	modelMatrix = glm::mat4(1.0f);
	///Move the Model to current position
	modelMatrix = glm::translate(modelMatrix, data.currentTransform.position);

	///Rotate the Model to Current Rotation
	modelMatrix = glm::rotate(modelMatrix,
		glm::radians(data.currentTransform.rotation.x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix,
		glm::radians(data.currentTransform.rotation.y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix,
		glm::radians(data.currentTransform.rotation.z), glm::vec3(0, 0, 1));

	///Scale the Model to Curret Scale
	modelMatrix = glm::scale(modelMatrix, data.currentTransform.scale);
}


///----------------------Load Model----------------------///
//Load Model at given directory
bool Model::loadModel(std::string modelDir)
{
	///Using the 'buLoadModel' function from 'bugl.h'
	///Load the desired Model and get the Amount of Vertices the Model has
	modelID = buLoadModel(modelDir, &vertexCount);
	///If creating Model was a success, then return NO error
	if (modelID)
	{
		std::cout << "\n\nEVENT: Loaded Model from path: " << modelDir;
		return true;
	}
	///If creating Model was a failure, then return as error
	else
	{
		std::cout << "\n\nERROR: Loading Model from path: " << modelDir;
		return false;
	}
}
//Load Model's Texture at given directory
bool Model::loadTexture(std::string textureDir)
{
	///Using 'stbi_load', load the PNG file from the given directory
	///Also get the dimensions of the image(width, height)
	const char* texDir = textureDir.data();
	textureData = stbi_load(texDir, &imageSize.x, &imageSize.y,
		NULL, 4);
	///If Loading the Model's Texture was a success
	if (textureData)
	{
		//std::cout << "\nEVENT: Texture Loaded from Path: " << textureDir;
	}
	///If Loading the Model's Texture was a failure, return as an error
	else
	{
		std::cout << "\nERROR Loading Texture from Path: " << textureDir;
		return false;
	}

	///From loaded texture data, create a texture ID
	glGenTextures(1, &textureID);
	///If successful
	if (textureID)
	{
		//std::cout << "\nEVENT: Created Texture";
	}
	///If failure, return as an error
	else
	{
		std::cout << "\nERROR Creating Texture";
		return false;
	}

	///Bind the Texture to be used by the model later
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize.x, imageSize.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	///Create a Mipmap of the created Texture
	glGenerateMipmap(GL_TEXTURE_2D);

	///The textureData is no longer needed, to empty
	free(textureData);

	///Return as success
	return true;
}



///----------------Render----------------///
//Using the Camera, Wireframe/Solid Model, Shader Choice
//Draw the Model into the 3D scene from the Camera's perspective
void Model::drawModel(Camera camera)
{
	///Create a new shaderProgram
	shaderProgram = ShaderProgram();
	shaderProgram.newShaderProgram(data.shaderType);

	///Using a Texture, set to THIS model
	glUseProgram(shaderProgram.getID());
	glActiveTexture(GL_TEXTURE + textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	///Using the model's vao id
	glBindVertexArray(modelID);

	///Set the shaderProgram's point of projection/camera position
	///to the Camera's Transform Matrix
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getID(), "u_Projection"),
		1, GL_FALSE, glm::value_ptr(camera.getTransformMatrix()));

	///Set the shaderProgram's Model position/transformation
	///to THIS Model's Transformation Matrix
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getID(), "u_Model"),
		1, GL_FALSE, glm::value_ptr(modelMatrix));

	///Use instruction, depending on specific drawType pass by
	switch (data.drawType)
	{
	///If the pass by is '0'
	case 0:
	{
		///Draw the Model as a Wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		///Draw the Model divided into Triangles
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertexCount);

		///Reset draw mode to fill object in
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	}

	///If the pass by is '1'
	case 1:
	{
		///Draw the Model divided into Triangles using the Model's
		///Number of Vertices
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertexCount);
		break;
	}
	}
}


///---------Get Default Transformation---------///
//Returns Model's Default Position
glm::vec3 Model::getDefaultPosition()
{
	return data.defaultTransform.position;
}
//Returns Model's Default Rotation
glm::vec3 Model::getDefaultRotation()
{
	return data.defaultTransform.rotation;
}
//Returns Model's Default Scale
glm::vec3 Model::getDefaultScale()
{
	return data.defaultTransform.scale;
}


///---------Get Current Transformation---------///
//Returns Model Transformation Matrix
glm::mat4 Model::getModelMatrix()
{
	return modelMatrix;
}
//Returns Model's Current Position
glm::vec3 Model::getPosition()
{
	return data.currentTransform.position;
}
//Returns Model's Current Rotation
glm::vec3 Model::getRotation()
{
	return data.currentTransform.rotation;
}
//Returns Model's Current Scale
glm::vec3 Model::getScale()
{
	return data.currentTransform.scale;
}


///--------------Get Model's...--------------///
//Returns Model's Obj Directory
std::string Model::getModelDir()
{
	return data.modelDir;
}
//Returns the Model's ID
GLuint Model::getModelID()
{
	return modelID;
}
//Returns the Model's Vertex Count
size_t Model::getVertexCount()
{
	return vertexCount;
}


///------------Get Model's Texture...------------///
//Returns Model's Texture's BMP Directory
std::string Model::getTextureDir()
{
	return data.textureDir;
}
//Returns Model's ID
GLuint Model::getTextureid()
{
	return textureID;
}
//Returns Model's Texture Data
unsigned char* Model::getTextureData()
{
	return textureData;
}
//Returns Model's Image Size(Dimensions)
SDL_Point Model::getImageSize()
{
	return imageSize;
}


///-----------------Shader Types-----------------///
//Returns the Shader used for THIS Model
int Model::getShaderType()
{
	return data.shaderType;
}
//Set THIS Model's Shader Type
void Model::setShaderType(int _shaderType)
{
	data.shaderType = _shaderType;
}


///------------------Draw Types------------------///
//Returns the Type used to Draw THIS Model
//As a Wireframe or fully(default)
int Model::getDrawType()
{
	return data.drawType;
}
//Set the Type to Draw THIS Model as
void Model::setDrawType(int _drawType)
{
	data.drawType = _drawType;
}