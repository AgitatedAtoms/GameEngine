///Include the Load Scene Class Header File
#include "LoadScene.h"


//Constructor
//loadFileName should be the name of the file
//the data is Loaded from
LoadScene::LoadScene(const char* loadFileName)
{
	///Save the file name to use later in class functions
	loadName = loadFileName;
	///Search the loadName string,
	///IF '.txt' is NOT INSIDE the string
	if (loadName.find(".txt") == std::string::npos)
	{
		///Add '.txt' onto the end
		///of the loadName string
		loadName.append(".txt");
	}
}

//Deconstructor
LoadScene::~LoadScene()
{ }


//Load the Save file
//Load and create 
bool LoadScene::loadDataFromFile(std::vector<Model>& modelList)
{
	std::ifstream loadFile(loadName);
	std::string line;
	std::string strToFind;

	//The Number of models to be loaded
	//from this save file
	int numOfSavedModels = 0;

	//Character - 48 = integer
	//Example: char 2(50) - 48 = int 2
	int asciiToInt = 48;


	///Search String 'line' to find the Number
	///of models in sthe Save File
	strToFind = "Model Count: ";

	///Load the First Line 
	std::getline(loadFile, line);

	///Check the string loaded to 'line'
	///and check if strToFind string is inside the loaded line
	if (line.find(strToFind) != std::string::npos)
	{
		///Change the value to an integer
		numOfSavedModels = line.at(strToFind.size()) - asciiToInt;
		///Print the Output
		std::cout << "\nFILE: " << loadName << " contains " << numOfSavedModels
			<< " Models to load";

		for (int i = 0; i < numOfSavedModels; i++)
		{
			sceneDataList.push_back(Data());
		}
	}
	///If strToFind is NOT inside 'line'
	else
	{
		///Print Error and return as false;
		std::cout << "\n\nERROR: Line 1 of " << loadName << ", should tell number"\
			"of models saved into the file. Loaded Line: " << line;
		return false;
	}
	

	///Add enough elements into vector,
	///in order to write ALL loaded data to
	int lineCount = 1;
	bool isNextLine = false;
	for (int curModel = 0; curModel < (int)sceneDataList.size(); curModel++)
	{
		std::cout << "\n";
		for(;;)
		{
			std::getline(loadFile, line);
			lineCount++;

			std::string modelDirStr = "Model Directory:";
			std::string textureDirStr = "Texture Directory:";

			std::string dPosStr = "Default Position:";
			std::string dRotStr = "Default Rotation:";
			std::string dScaStr = "Default Scale:";

			std::string cPosStr = "Current Position:";
			std::string cRotStr = "Current Rotation:";
			std::string cScaStr = "Current Scale:";

			std::string shaderTypeStr = "Shader Type:";
			std::string drawTypeStr = "Draw Type:";

			///------------Model's Directories------------///
			///Load Model's .obj File
			if (line.find(modelDirStr) != std::string::npos)
			{
				std::getline(loadFile, line);
				sceneDataList[curModel].modelDir = line;

				std::cout << "\nModel Dir: "
					<< sceneDataList[curModel].modelDir;
			}
			///Load Model's Texture File
			if (line.find(textureDirStr) != std::string::npos)
			{
				std::getline(loadFile, line);
				sceneDataList[curModel].textureDir = line;

				std::cout << "\nTexture Dir: "
					<< sceneDataList[curModel].textureDir;
			}


			///-------------Default Transform-------------///
			if (line.find(dPosStr) != std::string::npos)
			{
				glm::vec3 dPos{ 0.0f, 0.0f, 0.0f };

				std::getline(loadFile, line);
				dPos.x = std::stof(line);

				std::getline(loadFile, line);
				dPos.y = std::stof(line);

				std::getline(loadFile, line);
				dPos.z = std::stof(line);

				sceneDataList[curModel].defaultTransform.position = dPos;

				std::cout << "\nDefault Position: "
					<< sceneDataList[curModel].defaultTransform.position.x << ", "
					<< sceneDataList[curModel].defaultTransform.position.y << ", "
					<< sceneDataList[curModel].defaultTransform.position.z;
			}
			if (line.find(dRotStr) != std::string::npos)
			{
				glm::vec3 dRot{ 0.0f, 0.0f, 0.0f };

				std::getline(loadFile, line);
				dRot.x = std::stof(line);

				std::getline(loadFile, line);
				dRot.y = std::stof(line);

				std::getline(loadFile, line);
				dRot.z = std::stof(line);

				sceneDataList[curModel].defaultTransform.rotation = dRot;

				std::cout << "\nDefault Rotation: "
					<< sceneDataList[curModel].defaultTransform.rotation.x << ", "
					<< sceneDataList[curModel].defaultTransform.rotation.y << ", "
					<< sceneDataList[curModel].defaultTransform.rotation.z;
			}
			if (line.find(dScaStr) != std::string::npos)
			{
				glm::vec3 dSca{ 0.0f, 0.0f, 0.0f };

				std::getline(loadFile, line);
				dSca.x = std::stof(line);

				std::getline(loadFile, line);
				dSca.y = std::stof(line);

				std::getline(loadFile, line);
				dSca.z = std::stof(line);

				sceneDataList[curModel].defaultTransform.scale = dSca;

				std::cout << "\nDefault Scale: "
					<< sceneDataList[curModel].defaultTransform.scale.x << ", "
					<< sceneDataList[curModel].defaultTransform.scale.y << ", "
					<< sceneDataList[curModel].defaultTransform.scale.z;
			}

			///-------------Current Transform-------------///
			if (line.find(cPosStr) != std::string::npos)
			{
				glm::vec3 cPos{ 0.0f, 0.0f, 0.0f };

				std::getline(loadFile, line);
				cPos.x = std::stof(line);

				std::getline(loadFile, line);
				cPos.y = std::stof(line);

				std::getline(loadFile, line);
				cPos.z = std::stof(line);

				sceneDataList[curModel].currentTransform.position = cPos;

				std::cout << "\nCurrent Position: "
					<< sceneDataList[curModel].currentTransform.position.x << ", "
					<< sceneDataList[curModel].currentTransform.position.y << ", "
					<< sceneDataList[curModel].currentTransform.position.z;
			}
			if (line.find(cRotStr) != std::string::npos)
			{
				glm::vec3 cRot{ 0.0f, 0.0f, 0.0f };

				std::getline(loadFile, line);
				cRot.x = std::stof(line);

				std::getline(loadFile, line);
				cRot.y = std::stof(line);

				std::getline(loadFile, line);
				cRot.z = std::stof(line);

				sceneDataList[curModel].currentTransform.rotation = cRot;

				std::cout << "\nCurrent Rotation: "
					<< sceneDataList[curModel].currentTransform.rotation.x << ", "
					<< sceneDataList[curModel].currentTransform.rotation.y << ", "
					<< sceneDataList[curModel].currentTransform.rotation.z;
			}
			if (line.find(cScaStr) != std::string::npos)
			{
				glm::vec3 cSca{ 0.0f, 0.0f, 0.0f };

				std::getline(loadFile, line);
				cSca.x = std::stof(line);

				std::getline(loadFile, line);
				cSca.y = std::stof(line);

				std::getline(loadFile, line);
				cSca.z = std::stof(line);

				sceneDataList[curModel].currentTransform.scale = cSca;

				std::cout << "\nCurrent Scale: "
					<< sceneDataList[curModel].currentTransform.scale.x << ", "
					<< sceneDataList[curModel].currentTransform.scale.y << ", "
					<< sceneDataList[curModel].currentTransform.scale.z;
			}

			///------------Shader Type------------///
			if (line.find(shaderTypeStr) != std::string::npos)
			{
				std::getline(loadFile, line);
				sceneDataList[curModel].shaderType = std::stoi(line);

				std::cout << "\nShader Type: "
					<< sceneDataList[curModel].shaderType;
			}

			///-------------Draw Type-------------///
			if (line.find(drawTypeStr) != std::string::npos)
			{
				std::getline(loadFile, line);
				sceneDataList[curModel].drawType = std::stoi(line);

				std::cout << "\nDraw Type: "
					<< sceneDataList[curModel].drawType;

				break;
			}
		}
	}

	modelList.clear();
	for (int curModel = 0; curModel < (int)sceneDataList.size(); curModel++)
	{
		modelList.push_back(Model());
		modelList[curModel].newModel(sceneDataList[curModel]);
	}
	sceneDataList.clear();

	std::cout << "\n\nLoaded Models: " << modelList.size();
	std::cout << "\nLine Count: " << lineCount;

	///Return Success
	return true;
}