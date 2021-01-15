#pragma once
#ifndef SAVE_SCENE_H
#define SAVE_SCENE_H

#include <\myengine\contrib\glm/glm.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Additional.h"
struct Transform;
struct Data;


//This Class sends all Object's Transforms,
//Shader Types, and Draw Types into one saveSceneFile.txt
//To then be Loaded by LoadScene.h file
class SaveScene
{
///Private Variables
private:
	//The name of the Saved Scene File
	std::string saveName;
	//The List of Struct Data
	//All Object's Data saved into this std::vector
	std::vector<Data> sceneDataList;

///Public Functions
public:
	//Constructor
	SaveScene(const char* saveFileName);
	//Deconstructor
	~SaveScene();


	//Open file and write the Data of each object within the Scene
	//Saved Data = std::vector<Data>
	void saveDataToFile();
	
	
	//Add Pass By Object Values into sceneDataList
	//Call for each object within the scene to be saved
	void addToSaveDataList(Data dataToLoad);
};

#endif