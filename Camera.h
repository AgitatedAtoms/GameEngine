#pragma once
#ifndef CAMERA_H
#define CAMERA_H

///Includes Base SDL2 Functions, Data Types, etc.
#include <SDL2/SDL.h>

///Includes Base GLM Functions, Data Types, etc.
#include <\myengine\contrib\glm/glm.hpp>
///Includes more advanced GLM functions and calculations
#include <\myengine\contrib\glm/ext.hpp>


//Camera Class used to view the 3D OpenGL Scene
class Camera
{
///Private Camera Class Variables
private:
	//The Program window's (xPos, yPos, Width, Height)
	SDL_Rect windowRect{ 0, 0, 0, 0 };
	//The Camera's Field Of View
	float FOV = 0.0f;
	//The Near Plane for the Camera glm::perspective
	float nearPlane = 0.0f;
	//The Far Plane for the Camera glm::perspective
	float farPlane = 0.0f;

	///-----------Default Transformations-----------///
	//Default Camera Position
	glm::vec3 defaultPosition{ 0.0f, 0.0f, 0.0f };
	//Default Camera Rotation
	glm::vec3 defaultRotation{ 0.0f, 0.0f, 0.0f };

	///-----------Current Transformations-----------///
	//Camera's Transformation Matrix
	glm::mat4 transformMatrix{ 1.0f };
	//Camera's View Matrix
	glm::mat4 viewMatrix{ 1.0f };
	//Current Camera Position
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	//Current Camera Rotation
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };

	///---------Camera's Directioanl Vectors---------///
	//Camera's Up Direction
	glm::vec3 upVector{ 0.0f, 0.0f, 0.0f };
	//Camera's Forward Direction
	glm::vec3 forwardVector{ 0.0f, 0.0f, 0.0f };
	//Camera's Left Direction
	glm::vec3 leftVector{ 0.0f, 0.0f, 0.0f };

	///---------Camera's Speeds---------///
	//Camera's Move Speed
	float moveSpeed = 0.0f;
	//Camera's Accelerated Move Speed
	float fastMoveSpeed = 0.0f;
	//Camera's Rotation Speed
	float rotateSpeed = 0.0f;

	//Input decides if THIS Camera is Perspective
	//Or an Orthographic View
	bool isPerspective = false;

///Public Camera Class Functions
public:
	//Constructor
	Camera();
	//Deconstructor
	~Camera();


	///---------------------New Camera---------------------///
	//Function which creates a new camera passing in the
	//Default Camera Transformation
	//Camera Move speed
	void newCamera(SDL_Rect windowRect,
		float _FOV, float cameraNearPlane, float cameraFarPlane,
		glm::vec3 _defaultPosition, glm::vec3 _defaultRotation,
		float cameraSpeed, float fastCameraSpeed, float cameraRotationSpeed);


	///----------------Camera's Transformation----------------///
	//Create the Camera's Transformation Matrix from position and rotation
	void updateMatrix(SDL_Rect windowRect);
	//Calculated the Directional Vectors: Up, Forward, and Left Vectors
	//These vectors are used to strafe the camera around the scene
	//Up Vector (-upVector = Down Vector) Allows the Camera Movement along the Y axis
	//Forward Vector (-forwardvector = Back Vector) Forward and Back camera movement
	//Left Vector (-leftVector = Right Vector) Allows strafe movement Left and Right
	void updateVectors();


	//Update the Camera's Position using the new pass by value
	void updatePosition(glm::vec3 newPosition);
	//Update the Camera's Rotation using the new pass by value
	void updateRotation(glm::vec3 newRotation);
	

	///---------------Reset Camera---------------///
	//Reset the Camera's Transformation to it's Default Transformation
	//Reset the Position and Rotation
	void resetCamera();


	///===================Get Functions===================///
	//Returns the Program's Window Rect
	SDL_Rect getWindowRect();
	//Returns the Camera's FOV
	float getFOV();
	//Returns the Near Plane
	float getNearPlane();
	//Returns the Far Plane
	float getFarPlane();

	///------------Get Transformation------------///
	//Get the Camera's Transform Matrix
	glm::mat4 getTransformMatrix();

	//Get the Camera's View Matrix
	glm::mat4 getViewMatrix();

	//Get the Camera's Current Position
	glm::vec3 getPosition();
	//Get the Camera's Current Rotation
	glm::vec3 getRotation();

	///----------Get Directional Vectors----------///
	//Get the Camera's Current Up Vector
	glm::vec3 getUpVector();
	//Get the Camera's Current Forward Vector
	glm::vec3 getForwardVector();
	//Get the Camera's Current Left Vector
	glm::vec3 getLeftVector();

	///------------Get Camera Speeds------------///
	//Get the Camera's Default Move Speed
	float getMoveSpeed();
	//Get the Camera's Accelerated Move Speed
	float getFastMoveSpeed();
	//Get the Camera's Rotation Speed
	float getRotateSpeed();
};

#endif