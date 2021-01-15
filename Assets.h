#pragma once
#ifndef ASSETS_H
#define ASSETS_H


struct Assets
{
///=========================Model Assets=========================///
public:
	///---------------------Square Model---------------------///
	const char* planeDir = "/myengine/Model Assets/Plane.obj";

	///---------------------Cube Model---------------------///
	const char* cubeDir = "/myengine/Model Assets/Cube/Cube.obj";
	const char* cubeTexture1Dir = "/myengine/Model Assets/Cube/Cube_Texture1.png";
	const char* cubeTexture2Dir = "/myengine/Model Assets/Cube/Cube_Texture2.png";
	const char* cubeAlphaTextureDir = "/myengine/Model Assets/Cube/Cube_Texture1_50_alpha.png";


	///---------------------Circle Model---------------------///
	const char* circleDir = "/myengine/Model Assets/Circle/Circle.obj";

	///---------------------SphereModel---------------------///
	const char* sphereDir = "/myengine/Model Assets/Sphere/Sphere.obj";
	const char* sphereTextureDir = "/myengine/Model Assets/Sphere/Sphere_Texture.png";


	///---------------------Triangle Model---------------------///
	const char* triangleDir = "/myengine/Model Assets/Triangle/Triangle.obj";

	///---------------------Pyramid Model---------------------///
	const char* pyramidDir = "/myengine/Model Assets/Pyramid/Pyramid.obj";
	const char* pyramidTextureDir = "/myengine/Model Assets/Pyramid/Pyramid_Texture.png";


	///------------------Platonic Solid Model------------------///
	const char* platonicSolidDir = "/myengine/Model Assets/Platonic Solid/Platonic Solid.obj";
	const char* platonicSolidTextureDir = "/myengine/Model Assets/Platonic Solid/Platonic Solid Texture.png";


	///---------------------Transform Tool---------------------///
	const char* transformToolDir = "/myengine/Model Assets/Transform Tool/TransformTool.obj";
	const char* transformToolTextureDir = "/myengine/Model Assets/Transform Tool/TransformTool_Texture.png";


	///=========================Tool Panel=========================///
	const char* saveSceneIcon = "/myengine/Model Assets/UI/Save_Icon.bmp";

	const char* newSceneIcon = "/myengine/Model Assets/UI/New_Icon.bmp";

	///Square and Cube
	const char* squarePrimIcon = "/myengine/Model Assets/UI/Square_Icon.bmp";
	const char* cubePrimIcon = "/myengine/Model Assets/UI/Cube_Icon.bmp";

	///Circle and Sphere
	const char* circlePrimIcon = "/myengine/Model Assets/UI/Circle_Icon.bmp";
	const char* spherePrimIcon = "/myengine/Model Assets/UI/Sphere_Icon.bmp";

	///Triangle and Pyramid
	const char* trianglePrimIcon = "/myengine/Model Assets/UI/Triangle_Icon.bmp";
	const char* pyramidPrimIcon = "/myengine/Model Assets/UI/Pyramid_Icon.bmp";

	const char* loadSceneIcon = "/myengine/Model Assets/UI/Load_Icon.bmp";
};

#endif