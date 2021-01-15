#pragma once
#ifndef CLOCK_H
#define CLOCK_H

///Includes use of Base SDL Functions, Data Types, etc.
#include <SDL2/SDL.h>

///Includes use of 'std::clock_t'
#include <ctime>


//This Class 'Clock' is used to calculate deltaTime,
//And the Overlapped time of the program
class Clock
{
///Private Class Clock Variables
private:
	//Used to calculate the deltaTime
	float lastTime = 0.0f;
	//deltaTime used to Normalize Entity Move/Rotation/Scale speeds
	float deltaTime = 0.0f;

	//Overall time program has run for
	float gameTime = 0.0f;
	//Used to calculate the gameTime variable
	std::clock_t start = 0;

///Public Class Clock Functions
public:
	//Constructor
	//Start the Clock
	Clock();
	//Deconstructor
	~Clock();


	//Updates the deltaTime
	void updateClock();


	//Returns the deltaTime of current frame
	float getDeltaTime();


	//Returns the Overlapped Time the Program
	//has been running for
	float getGameTime();
};

#endif