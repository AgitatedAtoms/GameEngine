///Includes Base SDL2 Functions
#include <SDL2/SDL.h>
///Includes Image Loading and Rendering
#include <SDL2/SDL_image.h>

///Includes Base GLM functions
#include <\myengine\contrib\glm\glm.hpp>
///Includes Advanced GLM functions
#include <\myengine\contrib\glm\ext.hpp>

///Includes Base Glew functions/data types, etc.
#include <GL/glew.h>

///Includes Base std:: functions
#include <iostream>
///Includes std::shared_ptr
#include <memory>

///Calculates Delta Time and Overall Time
#include "myengine/Clock.h"
class Clock;

///Creates the Utility Window for THIS program
#include "myengine/ToolPanel.h"
class ToolPanel;

///Allows Creation of a Camera
#include "myengine/Camera.h"
class Camera;

///Includes the Input Handling of the program
#include "myengine/KeyboardAndMouse.h"
class KeyboardAndMouse;

///Includes creation of Model's with shaders
#include "myengine/ShaderProgram.h"
class ShaderProgram;

///Allows creation/loading/drawing of a Model
#include "myengine/Model.h"
class Model;

///Gets the directories of each Model and Texture
///Used in the program
#include "myengine/Assets.h"

///Include access Save Scene's class
///Enables Program to save the scene into
///a .txt file
#include "myengine/SaveScene.h"
class SaveScene;

///Include access to both structs Trasform and Data
///For storage ease
#include "myengine/Additional.h"
struct Transform;
struct Data;


//Prototype
void programLoop(SDL_Window* window, SDL_Rect windowRect);


//Where the program initializes before the programLoop func
int main(int argc, char* argv[])
{
	std::cout << "\n============Pre-Program============";
	SDL_Window* window = nullptr;
	SDL_Rect windowRect{ 155, 32, 1000, 750 };

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		///-----------------Init-----------------///
		std::cout << "\nInitialized SDL";
		windowRect = SDL_Rect{ windowRect.x, windowRect.y, windowRect.w, windowRect.h };

		window = SDL_CreateWindow("Black and White Shader",
			windowRect.x, windowRect.y, windowRect.w, windowRect.h,
			SDL_WINDOW_OPENGL);
		if (SDL_GL_CreateContext(window))
		{
			std::cout << "\nCreated OpenGL Window";
		}
		else
		{
			std::cout << "\n\nERROR: Creating OpenGL Window";
			return 0;
		}
		if (glewInit() == GLEW_OK)
		{
			std::cout << "\nInitialized Glew";
		}
		else
		{
			std::cout << "\n\nERROR: Initializing Glew";
			return 0;
		}

		
		programLoop(window, windowRect);
	}
	else
	{
		std::cout << "\n\nERROR: Initializing SDL";
	}

	std::cout << "\n\n\n";
	return 0;
}


//The Main Program Loop
void programLoop(SDL_Window* window, SDL_Rect windowRect)
{
	std::cout << "\n\n============Program Loop============";
	
	//The Name of the Saved File
	const char* saveFileName = "SaveFile";

	//Tool Panel Class object used as a Utility Window to the Main Program Window
	std::shared_ptr<ToolPanel> toolPanel = std::make_shared<ToolPanel>();
	toolPanel->createToolPanel(saveFileName);

	//List of Asset directories
	//Used to load Models and Textures from
	Assets assetList = Assets();

	///-----------------Camera-----------------///
	//Camera's Class Object
	Camera camera = Camera();

	//Camera's Field of View
	float FOV = 45.0f;
	//Camera's Near Plane
	float nearPlane = 0.1f;
	//Camera's Far Plane
	float farPlane = -1000.0f;

	//Set the default Camera Position and Rotation(No scale required)
	glm::vec3 defaultCameraPos{ -35.0f, -25.0f, -50.0f };
	glm::vec3 defaultCameraRot{ 30.0f, -35.0f, 0.0f };
	//The normal move speed for the camera
	float cameraSpeed = 10.0f;
	//The fast move speed for the camera
	float fastCameraSpeed = 20.0f;
	//The rotation speed for the camera
	float cameraRotationSpeed = 50.0f;

	///Create a new Perspective Camera with these variables
	camera.newCamera(windowRect,
		FOV, nearPlane, farPlane,
		defaultCameraPos, defaultCameraRot,
		cameraSpeed, fastCameraSpeed, cameraRotationSpeed);
	
	
	///---------------Plane Model---------------///
	Model planeObj = Model();

	//Plane Model Variables
	Data planeData = Data();

	///Set Plane Model's variables
	planeData.modelDir = assetList.planeDir;
	planeData.textureDir = "";

	planeData.defaultTransform.position = { 0.0f, 0.0f, 0.0f };
	planeData.defaultTransform.rotation = { 0.0f, 0.0f, 0.0f };
	planeData.defaultTransform.scale = { 20.0f, 20.0f, 20.0f };

	planeData.currentTransform = planeData.defaultTransform;

	planeData.shaderType = 2;
	planeData.drawType = 0;

	///Create a new Model with Plane Vairbales
	planeObj.newModel(planeData);
	
	
	///-----------------Transform Tool-----------------///
	Model transformTool = Model();
	
	//Transform Tool Model Variables
	Data transformToolData = Data();

	///Set TransformTool Data's Variables
	transformToolData.modelDir = assetList.transformToolDir;
	transformToolData.textureDir = assetList.transformToolTextureDir;

	transformToolData.defaultTransform.position = { 0.0f, -5.0f, 0.0f };
	transformToolData.defaultTransform.rotation = { 0.0f, 0.0f, 0.0f };
	transformToolData.defaultTransform.scale = { 3.0f, 3.0f, 3.0f };

	transformToolData.currentTransform = transformToolData.defaultTransform;

	transformToolData.shaderType = 1;
	transformToolData.drawType = 1;

	///Create a new Model with Transform Tool Vairbales
	transformTool.newModel(transformToolData);


	///-----------------Default Model Model-----------------///
	//The Move speed of each Model
	float modelMoveSpeed = 10.0f;
	//The Rotation speed of each Model
	float modelRotationSpeed = 40.0f;
	//The Scale speed of each Model
	float modelScaleSpeed = 5.0f;

	//The data held of EACH model created and altered
	std::vector<Model> modelList;
	//The maximum number of Model's within the scene
	int maxNumOfModels = 50;
	std::cout << "\nMaximum Number of Models in Scene: " << maxNumOfModels;

	//The default model data sent to create a working(no Modeled/Textured) model
	Data defaultModelData = Data();

	defaultModelData.modelDir = "";
	defaultModelData.textureDir = "";

	defaultModelData.defaultTransform.position = { 0.0f, 0.0f, 0.0f };
	defaultModelData.defaultTransform.rotation = { 0.0f, 0.0f, 0.0f };
	defaultModelData.defaultTransform.scale = { 2.0f, 2.0f, 2.0f };

	defaultModelData.currentTransform = defaultModelData.defaultTransform;

	defaultModelData.shaderType = 0;
	defaultModelData.drawType = 0;


	///----------------Background----------------///
	//Background Colour
	glm::vec4 background{ 102.0f, 200.0f, 240.0f, 255.0f };

	///------------------Clock------------------///
	//Clock Class Object
	//Used for deltaTime and Overall Time
	Clock clock = Clock();

	///---------Keyboard & Mouse Events---------///
	//Keyboard and Mouse Event handling
	KeyboardAndMouse keyMouse = KeyboardAndMouse();
	keyMouse.setModelSpeeds(modelMoveSpeed, modelRotationSpeed, modelScaleSpeed);
	
	//The currently selected Model
	// -1 = no model selected
	// 0 = first model created
	// ...
	int selectedModel = -1;

	///-----------------Program Loop-----------------///
	bool quit = false;
	while (!quit)
	{
		///Calculate new Delta Time
		clock.updateClock();
		
		///Create new Camera Transform Matrix
		///Also updates directional vectors
		camera.updateMatrix(windowRect);


		///-----------------Input Handling-----------------///
		//Get User's input
		SDL_Event event;
		SDL_PollEvent(&event);

		///Find instructions to input
		keyMouse.inputEvents(window,
			event, quit,
			clock.getDeltaTime(), camera,
			transformTool,
			selectedModel, maxNumOfModels, modelList);
		
		
		//Choice = Which item on Tool Panel was selected
		//Use choice to
		//save the scene, load a scene,
		//or Create shapes in the scene
		int choice = 0;
		toolPanel->checkClick(event, choice);
		if (choice != 0)
		{
			std::cout << "\nChoice: ";
			switch (choice)
			{
			case 1:
			{
				SaveScene* save = new SaveScene(saveFileName);

				for (int i = 0; i < (int)modelList.size(); i++)
				{
					Transform defaultTransform =
						Transform{ modelList[i].getDefaultPosition(),
									modelList[i].getDefaultRotation(),
									modelList[i].getDefaultScale() };

					Transform currentTransform =
						Transform{ modelList[i].getPosition(),
									modelList[i].getRotation(),
									modelList[i].getScale() };

					Data modelData =
						Data{ modelList[i].getModelDir(),
								modelList[i].getTextureDir(),
								defaultTransform, currentTransform,
								modelList[i].getShaderType(),
								modelList[i].getDrawType() };
					
					save->addToSaveDataList(modelData);
				}
				save->saveDataToFile();
				delete save;

				std::cout << "Save Scene";
				break;
			}
			case 2:
			{
				modelList.clear();
				camera.resetCamera();

				std::cout << "New Scene";
				break;
			}
				
			case 3:
			{
				if (modelList.size() != maxNumOfModels)
				{
					modelList.push_back(Model());
					Data newModelData = defaultModelData;
					newModelData.modelDir = assetList.planeDir;
					newModelData.textureDir = "";

					newModelData.shaderType = 1;
					newModelData.drawType = 1;

					modelList[(modelList.size() - 1)].newModel(newModelData);

					std::cout << "Square Primitive";
				}
				break;
			}
			case 4:
			{
				if (modelList.size() != maxNumOfModels)
				{
					modelList.push_back(Model());
					Data newModelData = defaultModelData;
					newModelData.modelDir = assetList.cubeDir;
					newModelData.textureDir = assetList.cubeAlphaTextureDir;

					newModelData.shaderType = 2;
					newModelData.drawType = 1;

					modelList[(modelList.size() - 1)].newModel(newModelData);

					std::cout << "Cube Primitive";
				}
				break;
			}

			case 5:
			{
				if (modelList.size() != maxNumOfModels)
				{
					modelList.push_back(Model());
					Data newModelData = defaultModelData;
					newModelData.modelDir = assetList.circleDir;
					newModelData.textureDir = "";

					newModelData.shaderType = 1;
					newModelData.drawType = 1;

					modelList[(modelList.size() - 1)].newModel(newModelData);

					std::cout << "Circle Primitive";
				}
				break;
			}
			case 6:
			{
				if (modelList.size() != maxNumOfModels)
				{
					modelList.push_back(Model());
					Data newModelData = defaultModelData;
					newModelData.modelDir = assetList.sphereDir;
					newModelData.textureDir = assetList.sphereTextureDir;

					newModelData.shaderType = 2;
					newModelData.drawType = 1;

					modelList[(modelList.size() - 1)].newModel(newModelData);

					std::cout << "Sphere Primitive";
				}
				break;
			}

			case 7:
			{
				if (modelList.size() != maxNumOfModels)
				{
					modelList.push_back(Model());
					Data newModelData = defaultModelData;
					newModelData.modelDir = assetList.triangleDir;
					newModelData.textureDir = "";

					newModelData.shaderType = 1;
					newModelData.drawType = 1;

					modelList[(modelList.size() - 1)].newModel(newModelData);

					std::cout << "Triangle Primitive";
				}
				break;
			}
			case 8:
			{
				if (modelList.size() != maxNumOfModels)
				{
					modelList.push_back(Model());
					Data newModelData = defaultModelData;
					newModelData.modelDir = assetList.pyramidDir;
					newModelData.textureDir = assetList.pyramidTextureDir;

					newModelData.shaderType = 2;
					newModelData.drawType = 1;

					modelList[(modelList.size() - 1)].newModel(newModelData);

					std::cout << "Pyramid Primitive";
				}
				break;
			}

			case 9:
			{
				LoadScene* load = new LoadScene(saveFileName);
				load->loadDataFromFile(modelList);
				delete load;

				std::cout << "Load Scene";
				break;
			}
			}
		}
	   
		
		///Ensure the Model List WILL NOT exceed the Model Count Maximum Limit
		if ((int)modelList.size() > maxNumOfModels)
		{
			///If TOO many models in the scene,
			///then delete the last one in the std::vector list
			modelList.pop_back();
		}
		

		///-----------------Background-----------------///
		///Set the background colour of 3D space to variable 'background'
		glClearColor(background.x / 255, background.y / 255,
			background.z / 255, background.w / 255);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Cull objects
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		//Blend objects(if object is translucent)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		//Enable depth to scene(no overlapping meshes)
		glEnable(GL_DEPTH_TEST);

		///Draw EACH model in modelList
		for (int i = 0; i < (int)modelList.size(); i++)
		{
			modelList[i].drawModel(camera);
		}

		///If a model is selected, then draw the trasformTool in Correct Position
		if(selectedModel != -1)
		{
			///To see tool from outside, disable depth of field and cull
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			transformTool.drawModel(camera);
		}


		///Enable Depth and Cull
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		///Draw the Plane - Net Floor
		planeObj.drawModel(camera);


		///Display Scene and reset for next loop
		glBindVertexArray(0);
		glUseProgram(0);
		SDL_GL_SwapWindow(window);
		glFlush();

		///Render the toolPanel on the 2nd SDL Window
		toolPanel->render();
	}

	std::cout << "\n============End Loop============";
}