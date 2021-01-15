///Access Camera's Header File
#include "Camera.h"


//Constructor
Camera::Camera()
{ }

//Deconstructor
Camera::~Camera()
{ }


///---------------------New Camera---------------------///
//Function which creates a new camera passing in the
//Default Camera Transformation
//Camera Move speed
void Camera::newCamera(SDL_Rect _windowRect,
	float _FOV, float cameraNearPlane, float cameraFarPlane,
	glm::vec3 _defaultPosition, glm::vec3 _defaultRotation,
	float cameraSpeed, float fastCameraSpeed, float cameraRotationSpeed)
{
	windowRect = _windowRect;
	FOV = _FOV;
	nearPlane = cameraNearPlane;
	farPlane = cameraFarPlane;

	///Set the Current and Default position and rotation to the pass in
	position = defaultPosition = _defaultPosition;
	rotation = defaultRotation = _defaultRotation;

	///Set the Camera's Move and Rotation Speed to pass in values
	moveSpeed = cameraSpeed;
	fastMoveSpeed = fastCameraSpeed;
	rotateSpeed = cameraRotationSpeed;

	///Create a glm::matrix from the Camera's Position and Rotation
	updateMatrix(windowRect);
}


///----------------Camera's Transformation----------------///
//Create the Camera's Transform Matrix from position and rotation
void Camera::updateMatrix(SDL_Rect windowRect)
{
	///Create a perspective camera matrix
	///glm::perspective(Field of View, Aspect Ration, Near Plane, Far Plane)
	transformMatrix = glm::perspective(glm::radians(FOV),
		(float)windowRect.w / (float)windowRect.h, nearPlane, farPlane);

	///Update the Matrix's rotation by the Camera's current Rotation
	transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	
	///Update the Matrix's position by the Camera's current Position
	transformMatrix = glm::translate(transformMatrix, position);

	///A new matrix needs new vectors
	updateVectors();

	///Create a View Matrix used for Ray Collision
	///(Selecting Objects in the Scene)
	viewMatrix = glm::lookAt(position, position + forwardVector, glm::vec3(0, 1, 0));
}

//Calculated the Directional Vectors: Up, Forward, and Left Vectors
//These vectors are used to strafe the camera around the scene
//Up Vector (-upVector = Down Vector) Allows the Camera Movement along the Y axis
//Forward Vector (-forwardvector = Back Vector) Forward and Back camera movement
//Left Vector (-leftVector = Right Vector) Allows strafe movement Left and Right
void Camera::updateVectors()
{
	///Get the Up Vector from the Camera's matrix
	upVector = glm::normalize(transformMatrix[1]);
	///Get the Forward Vector from negative the Camera's Matrix
	forwardVector = glm::normalize(-transformMatrix[2]);
	///Calculate the Left Vector from the Cross Productor between
	///the Up ad Forward Vector to get the left vector
	leftVector = glm::normalize(glm::cross(upVector, forwardVector));
}

//Update the Camera's Position using the new pass by value
void Camera::updatePosition(glm::vec3 newPosition)
{
	position += newPosition;
}

//Update the Camera's Rotation using the new pass by value
void Camera::updateRotation(glm::vec3 newRotation)
{
	rotation += newRotation;
}


///---------------Reset Camera---------------///
//Reset the Camera's Transformation to it's Default Transformation
//Reset the Position and Rotation
void Camera::resetCamera()
{
	position = defaultPosition;
	rotation = defaultRotation;
}


///===================Get Functions===================///
//Returns the Program's Window Rect
SDL_Rect Camera::getWindowRect()
{
	return windowRect;
}

//Returns the Camera's FOV
float Camera::getFOV()
{
	return FOV;
}

//Returns the Near Plane
float Camera::getNearPlane()
{
	return nearPlane;
}

//Returns the Far Plane
float Camera::getFarPlane()
{
	return farPlane;
}


///------------Get Transformation------------///
//Get the Camera's Transform Matrix
glm::mat4 Camera::getTransformMatrix()
{
	return transformMatrix;
}

//Get the Camera's View Matrix
glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

//Get the Camera's Current Position
glm::vec3 Camera::getPosition()
{
	return position;
}
//Get the Camera's Current Rotation
glm::vec3 Camera::getRotation()
{
	return rotation;
}


///----------Get Directional Vectors----------///
//Get the Camera's Current Up Vector
glm::vec3 Camera::getUpVector()
{
	return upVector;
}
//Get the Camera's Current Forward Vector
glm::vec3 Camera::getForwardVector()
{
	return forwardVector;
}
//Get the Camera's Current Left Vector
glm::vec3 Camera::getLeftVector()
{
	return leftVector;
}


///------------Get Camera Speeds------------///
//Get the Camera's Default Move Speed
float Camera::getMoveSpeed()
{
	return moveSpeed;
}
//Get the Camera's Accelerated Move Speed
float Camera::getFastMoveSpeed()
{
	return fastMoveSpeed;
}
//Get the Camera's Rotation Speed
float Camera::getRotateSpeed()
{
	return rotateSpeed;
}