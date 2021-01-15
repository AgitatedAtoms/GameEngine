#pragma once
#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <\myengine\contrib\glm/glm.hpp>

#include <string>


//Used to store an Object's
//Position, Rotation, and Scale within the Saved Scene
struct Transform
{
	//The Position of THIS Object
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	//The Rotation of THIS Object
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	//The Scale of THIS Object
	glm::vec3 scale{ 0.0f, 0.0f, 0.0f };
};


//std::vector<SaveData> list of scene's objects
//Information to be saved into saveFile.txt
struct Data
{
	//THIS Model's .obj File Directory
	std::string modelDir = "";
	//THIS Model's Texture File Directory
	std::string textureDir = "";

	//The Default Position, Rotation, and Scale of THIS Object
	Transform defaultTransform{ {0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{2.0f, 2.0f, 2.0f } };
	//The Current Position, Rotation, and Scale of THIS Object
	Transform currentTransform{ {0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{2.0f, 2.0f, 2.0f } };
	//The Shader used by THIS Object
	int shaderType = 0;
	//The Draw Type of THIS Object
	//Default or Wireframe draw
	int drawType = 0;
};

#endif