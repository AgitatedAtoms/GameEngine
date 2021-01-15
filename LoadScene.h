#pragma once
#ifndef LOAD_SCENE_H
#define LOAD_SCENE_H

///Includes Base GLM Functions, Data Types, etc.
#include <\myengine\contrib\glm/glm.hpp>
///Includes access to outside .txt save file
#include <fstream>
///Includes std::shared_ptr
#include <memory>
///Includes std::string
#include <string>

#include <stdio.h>

///Includes the Structs Transform and Data
///for model data storage
#include "myengine/Additional.h"
struct Transform;
struct Data;

///Includes the Model class
#include "myengine/Model.h"
class Model;


//This Class Takes an outside .txt file
//reads, and creates those saved models into the scene(modelList)
class LoadScene
{
///Private Class Variables
private:
	//The name of the Save File to Load
	std::string loadName;
	//The List of Struct Data
	//All Object's Data Loaded into this std::vector
	std::vector<Data> sceneDataList;

///Public Class Functions
public:
	//Constructor
	//loadFileName should be the name of the file
	//the data is Loaded from
	LoadScene(const char* loadFileName);
	//Deconstructor
	~LoadScene();


	//Load the Save file
	//Load and create 
	bool loadDataFromFile(std::vector<Model>& modelList);
};

#endif