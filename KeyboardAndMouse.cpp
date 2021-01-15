///Includes access to the KeyboardAndMouse Header File
#include "KeyboardAndMouse.h"


//Constructor
KeyboardAndMouse::KeyboardAndMouse()
{ }

//Deconstructor
KeyboardAndMouse::~KeyboardAndMouse()
{ }


//Set the NEW Model's created, default Transformation and speeds
void KeyboardAndMouse::setModelSpeeds(float _modelMoveSpeed, float _modelRotateSpeed, float _modelScaleSpeed)
{
	///Set Model's Move and Rotation Speeds
	modelMoveSpeed = _modelMoveSpeed;
	modelRotateSpeed = _modelRotateSpeed;
	modelScaleSpeed = _modelScaleSpeed;
}


//Gets user's Keyboard Input and sends back relevant instructions
void KeyboardAndMouse::inputEvents(SDL_Window* window, SDL_Event event,
	bool& quit, float deltaTime,
	Camera& camera,
	Model& transformTool,
	int& selectedModel,
	int modelListMax,
	std::vector<Model>& modelList)
{
	///Get the Camera's Move and Rotation Speed, then use deltaTime
	///To normalize the speed the Camera's speeds are at
	float cameraMoveSpeedD = camera.getMoveSpeed() * deltaTime;
	float cameraRotateSpeedD = camera.getRotateSpeed() * deltaTime;

	///Get the Selected Model's Move, Rotation, and Scale Speed, then use deltaTime
	///To normalize the speed the Model's speeds are at
	float modelMoveSpeedD = modelMoveSpeed * deltaTime;
	float modelRotateSpeedD = modelRotateSpeed * deltaTime;
	float modelScaleSpeedD = modelScaleSpeed * deltaTime;


	///If the Program' window is CLOSED,
	///OR if the user presses the ESCAPE Key
	///Return the program has been quit through reference
	if (event.type == SDL_QUIT ||
		event.type == SDL_KEYDOWN &&
		event.key.keysym.sym == SDLK_ESCAPE)
	{
		//std::cout << "\n\nINPUT: Quiting";
		quit = true;
		return;
	}

	///If the LEFT Mouse Button is clicked
	///then deselect all objects
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			selectedModel = -1;
		}
	}

	///If a Key pressed
	if (event.type == SDL_KEYDOWN)
	{
		///If the user presses the 'F' Key
		///Reset the Camera's Transformation
		///to its default values
		if (event.key.keysym.sym == SDLK_f)
		{
			camera.resetCamera();
		}
	}


	///Select Model Related by Keypad Number
	if (event.type == SDL_KEYDOWN)
	{
		///Depending on the Key Pressed
		switch (event.key.keysym.sym)
		{
			///If 'NUMPAD 0'
		case SDLK_KP_0:
			selectedModel = 0;
			break;
			///If 'NUMPAD 1'
		case SDLK_KP_1:
			selectedModel = 1;
			break;
			///If 'NUMPAD 2'
		case SDLK_KP_2:
			selectedModel = 2;
			break;
			///If 'NUMPAD 3'
		case SDLK_KP_3:
			selectedModel = 3;
			break;
			///If 'NUMPAD 4'
		case SDLK_KP_4:
			selectedModel = 4;
			break;
			///If 'NUMPAD 5'
		case SDLK_KP_5:
			selectedModel = 5;
			break;
			///If 'NUMPAD 6'
		case SDLK_KP_6:
			selectedModel = 6;
			break;
			///If 'NUMPAD 7'
		case SDLK_KP_7:
			selectedModel = 7;
			break;
			///If 'NUMPAD 8'
		case SDLK_KP_8:
			selectedModel = 8;
			break;
			///If 'NUMPAD 9'
		case SDLK_KP_9:
			selectedModel = 9;
			break;
		case SDLK_KP_DECIMAL:
			selectedModel = -1;
			break;
		}

		///If a Model IS selected
		if (selectedModel != -1)
		{
			///If the Maximum number of Models HAS NOT been reached
			if (selectedModel < (int)modelList.size())
			{
				//std::cout << "\n\nINPUT: Model " << (selectedModel + 1) << " selected";

				///Set the Transform tool's Position and Rotation to the Selected model's
				transformTool.updatePosition(modelList[selectedModel].getPosition());
				transformTool.updateRotation(modelList[selectedModel].getRotation());
			}
			///If the Maximum number of Models HAS been reached,
			///Reset the selected Model to NOTHING(-1 == Selected No Model)
			else
			{
				//std::cout << "\n\nERROR: There are not " << (selectedModel + 1)
				//	<< " models within the scene";
				selectedModel = -1;
			}
		}
	}

	///Reset the event.type value to 0 to avoid
	///accidental double calling instructions
	event.type = 0;

	///Get the keyboard's state(used to SDL_SCANCODE_(KEY))
	const Uint8* kbState = SDL_GetKeyboardState(NULL);

	///Wherever model is Moving, Rotating, or Scaling currently
	bool moveObject = false;
	bool rotationObject = false;
	bool scaleObject = false;

	///----------------------Model----------------------///
	///If a Model IS selected
	if (selectedModel != -1 &&
		modelList.size() > 0)
	{
		bool switchAxisToZ = false;
		if (kbState[SDL_SCANCODE_LALT])
		{
			switchAxisToZ = true;
		}


		///----------------Move Object----------------///
		///If the Input is 'Q' Key, MOVE the Selected Model
		if (kbState[SDL_SCANCODE_Q])
		{
			moveObject = true;
			rotationObject = false;
			scaleObject = false;
		}

		///If the UP ARROW is held down, MOVE the selected Model
		///in its UP direction
		if (kbState[SDL_SCANCODE_UP] &&
			moveObject == true)
		{
			//std::cout << "\nMove Object UP";
			modelList[selectedModel].updatePosition
			(modelList[selectedModel].getPosition() + glm::vec3{ 0.0f, modelMoveSpeedD, 0.0f });
		}
		///If the LEFT ARROW is held down, MOVE the selected Model
		///in its LEFT direction
		if (kbState[SDL_SCANCODE_LEFT] &&
			moveObject == true)
		{
			if (!switchAxisToZ)
			{
				//std::cout << "\nMove Object LEFT";
				modelList[selectedModel].updatePosition
				(modelList[selectedModel].getPosition() + glm::vec3{ -modelMoveSpeedD, 0.0f, 0.0f });
			}
			else
			{
				//std::cout << "\nMove Object CLOSER";
				modelList[selectedModel].updatePosition
				(modelList[selectedModel].getPosition() + glm::vec3{ 0.0f, 0.0f, modelMoveSpeedD });
			}
		}
		///If the DOWN ARROW is held down, MOVE the selected Model
		///in its DOWN direction
		if (kbState[SDL_SCANCODE_DOWN] &&
			moveObject == true)
		{
			//std::cout << "\nMove Object DOWN";
			modelList[selectedModel].updatePosition
			(modelList[selectedModel].getPosition() + glm::vec3{ 0.0f, -modelMoveSpeedD, 0.0f });
		}
		///If the RIGHT ARROW is held down, MOVE the selected Model
		///in its RIGHT direction
		if (kbState[SDL_SCANCODE_RIGHT] &&
			moveObject == true)
		{
			if (!switchAxisToZ)
			{
				//std::cout << "\nMove Object RIGHT";
				modelList[selectedModel].updatePosition
				(modelList[selectedModel].getPosition() + glm::vec3{ modelMoveSpeedD, 0.0f, 0.0f });
			}
			else
			{
				//std::cout << "\nMove Object AWAY";
				modelList[selectedModel].updatePosition
				(modelList[selectedModel].getPosition() + glm::vec3{ 0.0f, 0.0f, -modelMoveSpeedD });
			}
		}


		///----------------Rotate Object----------------///
		///If the Input is 'E' Key, ROTATE the Selected Model
		if (kbState[SDL_SCANCODE_E])
		{
			moveObject = false;
			rotationObject = true;
			scaleObject = false;
		}

		///If the UP ARROW is held down, ROTATE the selected Model
		///along the X axis to rotate the Model facing UP more
		if (kbState[SDL_SCANCODE_UP] &&
			rotationObject == true)
		{
			//std::cout << "\nRotate Object UP";
			modelList[selectedModel].updateRotation
			(modelList[selectedModel].getRotation() + glm::vec3{ -modelRotateSpeedD, 0.0f, 0.0f });
		}
		///If the LEFT ARROW is held down, ROTATE the selected Model
		///along the Y axis to rotate the Model facing LEFT more
		if (kbState[SDL_SCANCODE_LEFT] &&
			rotationObject == true)
		{
			if (!switchAxisToZ)
			{
				//std::cout << "\nRotate Object LEFT";
				modelList[selectedModel].updateRotation
				(modelList[selectedModel].getRotation() + glm::vec3{ 0.0f, -modelRotateSpeedD, 0.0f });
			}
			else
			{
				//std::cout << "\nRotate Object TOWARDS Camera";
				modelList[selectedModel].updateRotation
				(modelList[selectedModel].getRotation() + glm::vec3{ 0.0f, 0.0f, modelRotateSpeedD });
			}
		}
		///If the DOWN ARROW is held down, ROTATE the selected Model
		///along the X axis to rotate the Model facing DOWN more
		if (kbState[SDL_SCANCODE_DOWN] &&
			rotationObject == true)
		{
			//std::cout << "\nRotate Object DOWN";
			modelList[selectedModel].updateRotation
			(modelList[selectedModel].getRotation() + glm::vec3{ modelRotateSpeedD, 0.0f, 0.0f });
		}
		///If the RIGHT ARROW is held down, ROTATE the selected Model
		///along the Y axis to rotate the Model facing RIGHT more
		if (kbState[SDL_SCANCODE_RIGHT] &&
			rotationObject == true)
		{
			if (!switchAxisToZ)
			{
				//std::cout << "\nRotate Object LEFT";
				modelList[selectedModel].updateRotation
				(modelList[selectedModel].getRotation() + glm::vec3{ 0.0f, modelRotateSpeedD, 0.0f });
			}
			else
			{
				//std::cout << "\nRotate Object AWAY";
				modelList[selectedModel].updateRotation
				(modelList[selectedModel].getRotation() + glm::vec3{ 0.0f, 0.0f, -modelRotateSpeedD });
			}
		}


		///----------------Scale Object----------------///
		///If the Input is 'R' Key, SCALE the Selected Model
		if (kbState[SDL_SCANCODE_R])
		{
			moveObject = false;
			rotationObject = false;
			scaleObject = true;
		}

		///If the UP ARROW is held down, SCALE the selected Model
		///to be TALLER
		if (kbState[SDL_SCANCODE_UP] &&
			scaleObject)
		{
			//std::cout << "\nScale Object's Hight";
			modelList[selectedModel].updateScale
			(modelList[selectedModel].getScale() + glm::vec3{ 0.0f, modelScaleSpeedD, 0.0f });
		}
		///If the LEFT ARROW is held down, SCALE the selected Model
		///to be THINnER
		if (kbState[SDL_SCANCODE_LEFT] &&
			scaleObject)
		{
			if (!switchAxisToZ)
			{
				//std::cout << "\nScale Object's Width";
				modelList[selectedModel].updateScale
				(modelList[selectedModel].getScale() + glm::vec3{ -modelScaleSpeedD, 0.0f, 0.0f });
			}
			else
			{
				//std::cout << "\nScale Object's Depth";
				modelList[selectedModel].updateScale
				(modelList[selectedModel].getScale() + glm::vec3{ 0.0f, 0.0f, modelScaleSpeedD });
			}
		}
		///If the DOWN ARROW is held down, SCALE the selected Model
		///to be SHORTER
		if (kbState[SDL_SCANCODE_DOWN] &&
			scaleObject)
		{
			//std::cout << "\nScale Object's Height";
			modelList[selectedModel].updateScale
			(modelList[selectedModel].getScale() + glm::vec3{ 0.0f, -modelScaleSpeedD, 0.0f });
		}
		///If the RIGHT ARROW is held down, SCALE the selected Model
		///to be WIDER
		if (kbState[SDL_SCANCODE_RIGHT] &&
			scaleObject)
		{
			if (!switchAxisToZ)
			{
				//std::cout << "\nScale Object's Width";
				modelList[selectedModel].updateScale
				(modelList[selectedModel].getScale() + glm::vec3{ modelScaleSpeedD, 0.0f, 0.0f });
			}
			else
			{
				//std::cout << "\nScale Object's Depth";
				modelList[selectedModel].updateScale
				(modelList[selectedModel].getScale() + glm::vec3{ 0.0f, 0.0f, -modelScaleSpeedD });
			}
		}


		///---------------Reset Object---------------///
		///If the 'T' Key is Pressed/Held,
		///The Reset the selected Model's Transformation to
		///its default Transformation Values
		if (kbState[SDL_SCANCODE_T])
		{
			moveObject = false;
			rotationObject = false;
			scaleObject = false;
			modelList[selectedModel].resetModel();
		}

		///----------Update Transform Tool----------///
		if (modelList.size() > 0)
		{
			///As the Model has changed Position/Rotation/Scale,
			///Update the TransformationTool to the same Position and Rotation
			transformTool.updatePosition(modelList[selectedModel].getPosition());
			transformTool.updateRotation(modelList[selectedModel].getRotation());
		}
	} 


	///----------------Move Camera----------------///
	///If the 'LEFT SHIFT' Key is held,
	///Then ACCELERATE the Camera to it's fast Move Speed
	if (kbState[SDL_SCANCODE_LSHIFT])
	{
		cameraMoveSpeedD *= 2.5f;
	}

	//The NEW Position the Camera is moved to
	glm::vec3 newCameraPos{ 0.0f, 0.0f, 0.0f };
	
	///If the 'W' Key is held, then move the Camera
	///in the Camera's FORWARD Vector
	if (kbState[SDL_SCANCODE_W])
	{
		newCameraPos.x += cameraMoveSpeedD * camera.getForwardVector().x;
		newCameraPos.z += cameraMoveSpeedD * camera.getForwardVector().z;
	}
	///If the 'A' Key is held, then move the Camera
	///in the Camera's LEFT Vector
	if (kbState[SDL_SCANCODE_A])
	{
		newCameraPos.x += cameraMoveSpeedD * camera.getLeftVector().x;
		newCameraPos.z += cameraMoveSpeedD * camera.getLeftVector().z;
	}
	///If the 'S' Key is held, then move the Camera
	///in the Camera's -FORWARD Vector (Move Back)
	if (kbState[SDL_SCANCODE_S])
	{
		newCameraPos.x -= cameraMoveSpeedD * camera.getForwardVector().x;
		newCameraPos.z -= cameraMoveSpeedD * camera.getForwardVector().z;
	}
	///If the 'D' Key is held, then move the Camera
	///in the Camera's -LEFT Vector (Move Right)
	if (kbState[SDL_SCANCODE_D])
	{
		newCameraPos.x -= cameraMoveSpeedD * camera.getLeftVector().x;
		newCameraPos.z -= cameraMoveSpeedD * camera.getLeftVector().z;
	}

	///If the 'SPACE' Key is held, the move the Camera
	///UP along the Y Axis(Global)
	if (kbState[SDL_SCANCODE_SPACE])
	{
		newCameraPos.y -= cameraMoveSpeedD;
	}
	///If the 'LEFT CTRL' Key is held, the move the Camera
	///DOWN along the Y Axis(Global)
	if (kbState[SDL_SCANCODE_LCTRL])
	{
		newCameraPos.y += cameraMoveSpeedD;
	}

	///Update the camera to the new Position
	///Inside function, update the
	///UP, FORWARD, and LEFT Vectors
	camera.updatePosition(newCameraPos);


	///----------------Rotate Camera----------------///
	//The NEW Rotation the Camera is turned to
	glm::vec3 newCameraRot{ 0.0f, 0.0f, 0.0f };

	///If the UP ARROW is held, Rotate the Camera
	///facing UP
	if (kbState[SDL_SCANCODE_UP] &&
		!moveObject && !rotationObject && !scaleObject)
	{
		newCameraRot.x -= cameraRotateSpeedD;
	}
	///If the LEFT ARROW is held, Rotate the Camera
	///facing LEFT
	if (kbState[SDL_SCANCODE_LEFT] &&
		!moveObject && !rotationObject && !scaleObject)
	{
		newCameraRot.y -= cameraRotateSpeedD;
	}
	///If the DOWN ARROW is held, Rotate the Camera
	///facing DOWN
	if (kbState[SDL_SCANCODE_DOWN] &&
		!moveObject && !rotationObject && !scaleObject)
	{
		newCameraRot.x += cameraRotateSpeedD;
	}
	///If the RIGHT ARROW is held, Rotate the Camera
	///facing RIGHT
	if (kbState[SDL_SCANCODE_RIGHT] &&
		!moveObject && !rotationObject && !scaleObject)
	{
		newCameraRot.y += cameraRotateSpeedD;
	}

	///Update the camera to the new Rotation
	///Inside function, update the
	///UP, FORWARD, and LEFT Vectors
	camera.updateRotation(newCameraRot);
}