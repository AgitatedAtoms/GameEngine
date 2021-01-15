#pragma once
#ifndef TOOL_PANEL_H
#define TOOL_PANEL_H

///Includes Base SDL2 Functions, Data Types, etc.
#include <SDL2/SDL.h>
///Includes SDL2 Image Functions, Data Types, etc.
#include <SDL2/SDL_image.h>

///Includes std::cout (mainly used)
#include <iostream>

#include <filesystem>

#include "myengine/LoadScene.h"
class LoadScene;

#include "Assets.h"


//ToolPanel Class is used to serve as tool to the OpenGL scene
//Clear the scene, add primitives like 2D shapes or 3D Model's
class ToolPanel
{
///ToolPanel Class Private Variables
private:
	//The Renderer's display output
	SDL_Window* window = nullptr;
	//The Textures are drawn onto
	SDL_Renderer* renderer = nullptr;
	//The Position, Width, and Height on Monitor
	SDL_Rect toolWindowRect{ 0, 0, 0, 0 };

	///----------------Rects and Textures----------------///
	//Texture of Asset
	//Texture's Position, Width and Height on Renderer

	SDL_Texture* saveSceneTex = nullptr;
	SDL_Rect saveSceneRect{ 2, 10, 75, 75 };

	SDL_Texture* newSceneTex = nullptr;
	SDL_Rect newSceneRect{ 73, 10, 75, 75 };


	SDL_Texture* squarePrimTex = nullptr;
	SDL_Rect squarePrimRect{ 2, 90, 75, 75 };

	SDL_Texture* cubePrimTex = nullptr;
	SDL_Rect cubePrimRect{ 73, 90, 75, 75 };


	SDL_Texture* circlePrimTex = nullptr;
	SDL_Rect circlePrimRect{ 2, 165, 75, 75 };
	
	SDL_Texture* spherePrimTex = nullptr;
	SDL_Rect spherePrimRect{ 73, 165, 75, 75 };


	SDL_Texture* trianglePrimTex = nullptr;
	SDL_Rect trianglePrimRect{ 2, 240, 75, 75 };
	
	SDL_Texture* pyramidPrimTex = nullptr;
	SDL_Rect pyramidPrimRect{ 73, 240, 75, 75 };

	SDL_Texture* loadSceneTex = nullptr;
	SDL_Rect loadSceneRect{ 2, 315, 75, 75 };

///ToolPanel Class Public Functions
public:
	//Constructor
	ToolPanel();
	//Deconstructor
	~ToolPanel();


	//Create Tool Panel SDL_Window and SDL_Renderer
	//Creates SDL_Textures from SDL_Surface using BMP image files
	bool createToolPanel(const char* saveFileName);


	//Choices:
	// 1 = Save
	// 2 = New
	// 3 = Square
	// 4 = Cube
	// 5 = Circle
	// 6 = Sphere
	// 7 = Triangle
	// 8 = Pyramid
	void checkClick(SDL_Event& event, int& choice);
	

	//Render Tool Panel Window
	//Render Sprites
	void render();


	//Function that takes a X, Y positions, and Width and Height of a square/rectangle
	//Also takes mouse click position
	//Returns if mouse click is inside the box/SDL_Rect
	bool boxCheck(SDL_Point mousePos, SDL_Rect boxToCheck);
	

	//Takes the SDL_Renderer and the path of the BMP texture you wish to load
	//Returns a SDL_Texture*
	bool loadTextureBMPFromPath(SDL_Renderer* renderer, const char* bmpTexturePath, SDL_Texture** outputTexture);
};

#endif