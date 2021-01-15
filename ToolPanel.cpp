///Allows Access to the ToolPanel's Header File
#include "ToolPanel.h"


//Constructor
ToolPanel::ToolPanel()
{ }

//Deconstructor
ToolPanel::~ToolPanel()
{ }


//Create Tool Panel SDL_Window and SDL_Renderer
//Creates SDL_Textures from SDL_Surface using BMP image files
bool ToolPanel::createToolPanel(const char* saveFileName)
{
	///Creates a new SDL_Window(Window name, xPos(on monitor), yPos, Width, Height, SDL Window Flags)
	window = SDL_CreateWindow("Tool Window", 2, 32, 150, 500, 0);
	///If creation of window is successful
	if (window)
	{
		std::cout << "\nEVENT: Created Tool Window.";
	}
	///If Failure
	else
	{
		std::cout << "\n\nERROR: Creating Tool Window.";
		///Escape and return as an error
		return false;
	}

	///Creates a new SDL_Renderer(SDL_Window, window index, SDL Renderer Flags)
	renderer = SDL_CreateRenderer(window, -1, 0);
	///If creation of renderer is successful
	if (renderer)
	{
		std::cout << "\nEVENT: Tool Renderer Created.";
	}
	///If Failure
	else
	{
		std::cout << "\n\nERROR: Creating Tool Renderer.";
		///Return from function as an error
		return false;
	}

	///Set the default Background colour to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	
	///Call function to create texture from:
	///SDL_Renderer
	///BMP file directory
	///Turn SDL_Surface to SDL_Texture
	///Returns if function was success or not
	Assets assetList = Assets();
	if (!loadTextureBMPFromPath(renderer, assetList.saveSceneIcon, &saveSceneTex))
	{
		return false;
	}
	if (!loadTextureBMPFromPath(renderer, assetList.newSceneIcon, &newSceneTex))
	{
		return false;
	}

	if (!loadTextureBMPFromPath(renderer, assetList.squarePrimIcon, &squarePrimTex))
	{
		return false;
	}
	if (!loadTextureBMPFromPath(renderer, assetList.cubePrimIcon, &cubePrimTex))
	{
		return false;
	}

	if (!loadTextureBMPFromPath(renderer, assetList.circlePrimIcon, &circlePrimTex))
	{
		return false;
	}
	if (!loadTextureBMPFromPath(renderer, assetList.spherePrimIcon, &spherePrimTex))
	{
		return false;
	}

	if (!loadTextureBMPFromPath(renderer, assetList.trianglePrimIcon, &trianglePrimTex))
	{
		return false;
	}
	if (!loadTextureBMPFromPath(renderer, assetList.pyramidPrimIcon, &pyramidPrimTex))
	{
		return false;
	}

	std::string fileName = saveFileName;
	if (fileName.find(".txt") == std::string::npos)
	{
		///Add '.txt' onto the end
		///of the saveName string
		fileName.append(".txt");
	}

	bool saveFile = std::experimental::filesystem::exists(fileName);
	if (saveFile)
	{
		std::cout << "\nFound Save File: " << saveFileName;
		if (!loadTextureBMPFromPath(renderer, assetList.loadSceneIcon, &loadSceneTex))
		{
			return false;
		}
	}
	else
	{
		std::cout << "\nNo Save File Exists: " << saveFileName;
	}


	///The function is a success, return as NO error
	std::cout << "\nEVENT: Successfuly Loaded Tool Panel Textures";
	return true;
}


//Choices:
// 1 = Save
// 2 = New
// 3 = Square
// 4 = Cube
// 5 = Circle
// 6 = Sphere
// 7 = Triangle
// 8 = Pyramid
// 9 = Load Scene
void ToolPanel::checkClick(SDL_Event& event, int& choice)
{
	///If the Mouse as been Clicked
	if (event.type == SDL_MOUSEBUTTONDOWN &&
		event.window.windowID == SDL_GetWindowID(window))
	{
		///If the Left Button was Clicked
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			///Get the Position the mouse was clicked at
			///SDL_Point(int x, int y)
			SDL_Point mousePos{ 0, 0 };
			SDL_GetMouseState(&mousePos.x, &mousePos.y);


			///Using the boxCheck function, check if SDL_Texture is clicked on
			///Return relevant choice

			if (boxCheck(mousePos, saveSceneRect))
			{
				choice = 1;
			}
			if (boxCheck(mousePos, newSceneRect))
			{
				choice = 2;
			}

			if (boxCheck(mousePos, squarePrimRect))
			{
				choice = 3;
			}
			if (boxCheck(mousePos, cubePrimRect))
			{
				choice = 4;
			}

			if (boxCheck(mousePos, circlePrimRect))
			{
				choice = 5;
			}
			if (boxCheck(mousePos, spherePrimRect))
			{
				choice = 6;
			}

			if (boxCheck(mousePos, trianglePrimRect))
			{
				choice = 7;
			}
			if (boxCheck(mousePos, pyramidPrimRect))
			{
				choice = 8;
			}

			if (boxCheck(mousePos, loadSceneRect))
			{
				choice = 9;
			}
		}

		///Reset click to 0,
		///Make one click one call of this function
		event.button.button = 0;
	}
}


//Render Tool Panel Window
//Render Sprites
void ToolPanel::render()
{
	///Clear the SDL_Renderer before Copying any SDL_Textures
	SDL_RenderClear(renderer);

	///Add SDL_Texture's to Renderer at Position, with Scale
	SDL_RenderCopy(renderer, saveSceneTex, NULL, &saveSceneRect);
	SDL_RenderCopy(renderer, newSceneTex, NULL, &newSceneRect);

	SDL_RenderCopy(renderer, squarePrimTex, NULL, &squarePrimRect);
	SDL_RenderCopy(renderer, cubePrimTex, NULL, &cubePrimRect);

	SDL_RenderCopy(renderer, circlePrimTex, NULL, &circlePrimRect);
	SDL_RenderCopy(renderer, spherePrimTex, NULL, &spherePrimRect);

	SDL_RenderCopy(renderer, trianglePrimTex, NULL, &trianglePrimRect);
	SDL_RenderCopy(renderer, pyramidPrimTex, NULL, &pyramidPrimRect);

	SDL_RenderCopy(renderer, loadSceneTex, NULL, &loadSceneRect);

	///Display the renderer so user can see in created SDL_Window
	SDL_RenderPresent(renderer);
}


//Function that takes a X, Y positions, and Width and Height of a square/rectangle
//Also takes mouse click position
//Returns if mouse click is inside the box/SDL_Rect
bool ToolPanel::boxCheck(SDL_Point mousePos, SDL_Rect boxToCheck)
{
	if (mousePos.x > boxToCheck.x && mousePos.x < (boxToCheck.x + boxToCheck.w)
		&& mousePos.y > boxToCheck.y && mousePos.y < (boxToCheck.y + boxToCheck.h))
	{
		return true;
	}
	return false;
}


//Takes the SDL_Renderer and the path of the BMP texture you wish to load
//Returns a SDL_Texture*
bool ToolPanel::loadTextureBMPFromPath(SDL_Renderer* renderer, const char* bmpTexturePath, SDL_Texture** outputTexture)
{
	//Loads the BMP image using the SDL_LoadBMP function
	//Loads as SDL_Surface*
	SDL_Surface* tmp = SDL_LoadBMP(bmpTexturePath);
	if (!tmp)
	{
		std::cout << "\n\nERROR: Loading BMP File from Path: " << bmpTexturePath;
		return false;
	}
	//Using the SDL_Renderer, and SDL_Surface 'tmp' create a SDL_Texture*
	*outputTexture = SDL_CreateTextureFromSurface(renderer, tmp);
	
	//Empty the SDL_Surface* 'tmp'
	SDL_FreeSurface(tmp);

	///Checks if SDL_Texture is created Successfully
	if (!outputTexture)
	{
		std::cout << "\n\nERROR: Creating Texture From Surface";
		return false;
	}

	//Return the SDL_Texture value
	return true;
}