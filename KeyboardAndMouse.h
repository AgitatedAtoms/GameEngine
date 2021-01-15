#pragma once
#ifndef KEYBOARD_AND_MOUSE_H
#define KEYBOARD_AND_MOUSE_H

///Includes Base SDL2 Functions, Data Types, etc.
#include <SDL2/SDL.h>

///Includes Base GLM Functions, Data Types, etc.
#include <\myengine\contrib\glm/glm.hpp>

///Includes access to the Camera's Class
#include "myengine/Camera.h"
class Camera;

#include "myengine/Additional.h"
struct Transform;
struct Data;

///Includes access to the Model's Class
#include "myengine/Model.h"
class Model;

///Include access to the Assets'
///Model and Texture Directories
#include "myengine/Assets.h"



//This Class 'KeyboardAndMouse' is used
//to read the user's input
class KeyboardAndMouse
{
///Private Class Variable
private:
	///-------Model Speeds-------///
	float modelMoveSpeed = 0.0f;
	float modelRotateSpeed = 0.0f;
	float modelScaleSpeed = 0.0f;

///Public Class Functions
public:
	//Constructor
	KeyboardAndMouse();
	//Deconstructor
	~KeyboardAndMouse();


	//Set the NEW Model's created, default Transformation and speeds
	void setModelSpeeds(float _modelMoveSpeed, float _modelRotateSpeed, float _modelScaleSpeed);


	//Gets user's Keyboard Input and sends back relevant instructions
	void inputEvents(SDL_Window* window, SDL_Event event,
		bool& quit, float deltaTime,
		Camera& camera,
		Model& transformTool,
		int& selectedModel,
		int modelListMax,
		std::vector<Model>& modelList);
};

#endif