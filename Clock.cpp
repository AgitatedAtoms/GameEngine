///Includes access to Clock Class' Header File
#include "Clock.h"


//Constructor
//Start the Clock
Clock::Clock()
{
	start = std::clock();
}

//Deconstructor
Clock::~Clock()
{ }


//Updates the deltaTime
void Clock::updateClock()
{
	float timeNow = (float)SDL_GetTicks();
	deltaTime = (float)((timeNow - lastTime) / 1000.0f);
	lastTime = timeNow;
}


//Returns the deltaTime of current frame
float Clock::getDeltaTime()
{
	return deltaTime;
}


//Returns the Overlapped Time the Program
//has been running for
float Clock::getGameTime()
{
	return (float)(((float)std::clock() - (float)start) / (float)CLOCKS_PER_SEC);
}