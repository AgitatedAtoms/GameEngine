#pragma once
#ifndef MODEL_H
#define MODEL_H

///Include Glew functions
#include <GL/glew.h>
///Include Base GLM Functions, Data Types, etc.
#include <\myengine\contrib\glm/glm.hpp>
///Includes Advanced GLM Functions, etc.
#include <\myengine\contrib\glm/ext.hpp>

///Include use of the Model Loading given by Lecturer
#include <bugl.h>

///Include std::string
#include <string>

///Include use of ShaderProgram Class
#include "myengine/ShaderProgram.h"
class ShaderProgram;
///Incluude use of Camera Class
#include "myengine/Camera.h"
class Camera;

#include "myengine/Additional.h"
struct Transform;
struct Data;


//This class is used as a Blueprint for all models
//It holds the Model's Transformation Vectors and Matrix
//It also loads the Model and Textures
class Model
{
///Private Class Variables
private:
	///---------------3D Model---------------///
	//The id of THIS model
	GLuint modelID = 0;
	//The Number of Vertices in THIS Mdoel
	size_t vertexCount = 0;


	///---------------Model's Texture---------------///
	//The id of THIS Model's Texture
	GLuint textureID = 0;
	//The Texture Data Loaded from the directory
	unsigned char* textureData = nullptr;
	//The Image's Dimensions
	SDL_Point imageSize{ 0, 0 };


	///---------------Current Transform---------------///
	//The Transformation Matrix of THIS Model
	glm::mat4 modelMatrix{ 1.0f };


	///---------------------Shaders---------------------///
	//The Shader Program(Vertex and Fragment Shader used) for THIS model
	ShaderProgram shaderProgram;


	///----------Model Data----------///
	Data data;

///Public Class Functions
public:
	//Constructor
	Model();
	//Deconstructor
	~Model();


	//Creates a new model using pass by Default Transformation, Model and Texture Directories
	void newModel(Data _modelData);


	//Reset THIS Model's Transform to its Default Values
	void resetModel();


	///------------------Current Transformation------------------///
	//Updates the Current Model's Position to the newPosition values
	void updatePosition(glm::vec3 newPosition);
	//Updates the Current Model's Rotation to the newRotation values
	void updateRotation(glm::vec3 newRotation);
	//Updates the Current Model's Scale to the newScale values
	void updateScale(glm::vec3 newScale);
	//Updates the Current Model's Transformation Matrix
	void updateModelMatrix();


	///----------------------Load Model----------------------///
	//Load Model at given directory
	bool loadModel(std::string modelDir);
	//Load Model's Texture at given directory
	bool loadTexture(std::string textureDir);


	///----------------Render----------------///
	//Using the Camera, Wireframe/Solid Model, Shader Choice
	//Draw the Model into the 3D scene from the Camera's perspective
	void drawModel(Camera camera);


	///---------Get Default Transformation---------///
	//Returns Model's Default Position
	glm::vec3 getDefaultPosition();
	//Returns Model's Default Rotation
	glm::vec3 getDefaultRotation();
	//Returns Model's Default Scale
	glm::vec3 getDefaultScale();


	///---------Get Current Transformation---------///
	//Returns Model Transformation Matrix
	glm::mat4 getModelMatrix();
	//Returns Model's Current Position
	glm::vec3 getPosition();
	//Returns Model's Current Rotation
	glm::vec3 getRotation();
	//Returns Model's Current Scale
	glm::vec3 getScale();


	///--------------Get Model's...--------------///
	//Returns Model's Obj Directory
	std::string getModelDir();
	//Returns the Model's ID
	GLuint getModelID();
	//Returns the Model's Vertex Count
	size_t getVertexCount();


	///------------Get Model's Texture...------------///
	//Returns Model's Texture's BMP Directory
	std::string getTextureDir();
	//Returns Model's ID
	GLuint getTextureid();
	//Returns Model's Texture Data
	unsigned char* getTextureData();
	//Returns Model's Image Size(Dimensions)
	SDL_Point getImageSize();


	///----------Shader & Draw Types----------///
	//Returns the Shader used for THIS Model
	int getShaderType();
	//Set THIS Model's Shader Type
	void setShaderType(int _shaderType);

	//Returns the Type used to Draw THIS Model
	//As a Wireframe or fully(default)
	int getDrawType();
	//Set the Type to Draw THIS Model as
	void setDrawType(int _drawType);
};

#endif