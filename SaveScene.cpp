#include "SaveScene.h"


//Constructor
//saveFileName should be the name of the file
//the data is saved to
SaveScene::SaveScene(const char* saveFileName)
{
	///Save the file name to use later in class functions
	saveName = saveFileName;
	///Search the saveName string,
	///IF '.txt' is NOT INSIDE the string
	if (saveName.find(".txt") == std::string::npos)
	{
		///Add '.txt' onto the end
		///of the saveName string
		saveName.append(".txt");
	}
}

//Deconstructor
SaveScene::~SaveScene()
{
	///Clear the std::string name
	saveName.clear();
	///Clear the std::vector
	sceneDataList.clear();
}


//Open file and write the Data of each object within the Scene
//Saved Data = std::vector<Data>
void SaveScene::saveDataToFile()
{
	///Load the txt file named saveName
	std::ofstream saveFile;
	///Open the txt file to write into
	saveFile.open(saveName);
	saveFile.clear();

	///Save the Number of Model into the .txt file
	///This value is used to search for THAT amount of models
	///to load into the scene when called for
	saveFile << "Model Count: " << sceneDataList.size();

	///Loop through the list of Model Data
	///to send into save file
	for (int i = 0; i < (int)sceneDataList.size(); i++)
	{
		///State which object this data comes from
		saveFile << "\n\n\n========Object " << i << " Data========";

		///---------Model Directories---------///
		saveFile << "\n------------Model------------";
		if (sceneDataList[i].modelDir != "")
		{
			saveFile << "\nModel Directory:\n"
				<< sceneDataList[i].modelDir;
		}

		if (sceneDataList[i].textureDir != "")
		{
			saveFile << "\nTexture Directory:\n"
				<< sceneDataList[i].textureDir;
		}

		///---------Default Transform---------///
		///Make clean for easy reading of the .txt file
		saveFile << "\n-----Defaut Transformation-----";
		///Send in the Current Model's Default Transform's Position Data
		saveFile << "\nDefault Position:\n"
			<< sceneDataList[i].defaultTransform.position.x << "\n"
			<< sceneDataList[i].defaultTransform.position.y << "\n"
			<< sceneDataList[i].defaultTransform.position.z;

		///Send in the Current Model's Default Transform's Rotation Data
		saveFile << "\nDefault Rotation:\n"
			<< sceneDataList[i].defaultTransform.rotation.x << "\n"
			<< sceneDataList[i].defaultTransform.rotation.y << "\n"
			<< sceneDataList[i].defaultTransform.rotation.z;

		///Send in the Current Model's Default Transform's Scale Data
		saveFile << "\nDefault Scale:\n"
			<< sceneDataList[i].defaultTransform.scale.x << "\n"
			<< sceneDataList[i].defaultTransform.scale.y << "\n"
			<< sceneDataList[i].defaultTransform.scale.z;


		///---------Current Transform---------///
		///Make clean for easy reading of the .txt file
		saveFile << "\n----Current Transformation----";
		///Send in the Current Model's Current Transform's Position Data
		saveFile << "\nCurrent Position:\n"
			<< sceneDataList[i].currentTransform.position.x << "\n"
			<< sceneDataList[i].currentTransform.position.y << "\n"
			<< sceneDataList[i].currentTransform.position.z;

		///Send in the Current Model's Current Transform's Rotation Data
		saveFile << "\nCurrent Rotation:\n"
			<< sceneDataList[i].currentTransform.rotation.x << "\n"
			<< sceneDataList[i].currentTransform.rotation.y << "\n"
			<< sceneDataList[i].currentTransform.rotation.z;

		///Send in the Current Model's Current Transform's Scale Data
		saveFile << "\nCurrent Scale:\n"
			<< sceneDataList[i].currentTransform.scale.x << "\n"
			<< sceneDataList[i].currentTransform.scale.y << "\n"
			<< sceneDataList[i].currentTransform.scale.z;


		///------------Shader Type------------///
		///Send in the Current Model's Shader Type Data
		saveFile << "\n------Shader Type------";
		saveFile << "\nShader Type:\n"
			<< sceneDataList[i].shaderType;


		///-------------Draw Type-------------///
		///Send in the Current Model's Draw Type Data
		saveFile << "\n-------Draw Type-------";
		saveFile << "\nDraw Type:\n"
			<< sceneDataList[i].drawType;
	}

	///All Scene data is saved
	///Close the .txt file
	saveFile.close();
}


//Add Pass By Object Values into sceneDataList
//Call for each object within the scene to be saved
void SaveScene::addToSaveDataList(Data dataToLoad)
{
	///Add a new position in the sceneDataList to write to.
	///The pass by Object's data is sent into THIS new position
	sceneDataList.push_back(Data());

	///Send Obect's Model .obj File Directory into the list
	sceneDataList[(sceneDataList.size() - 1)].modelDir = dataToLoad.modelDir;
	///Send Obect's Model Texture File Directory into the list
	sceneDataList[(sceneDataList.size() - 1)].textureDir = dataToLoad.textureDir;

	///Send Object's Default Transform into the list
	sceneDataList[(sceneDataList.size() - 1)].defaultTransform = dataToLoad.defaultTransform;
	///Send Object's Current Transform into the list
	sceneDataList[(sceneDataList.size() - 1)].currentTransform = dataToLoad.currentTransform;
	///Send Object's Shader Type into the list
	sceneDataList[(sceneDataList.size() - 1)].shaderType = dataToLoad.shaderType;
	///Send Object's Draw Type into the list
	sceneDataList[(sceneDataList.size() - 1)].drawType = dataToLoad.drawType;
}