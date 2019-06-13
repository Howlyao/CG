#pragma once
#ifndef SCENE
#define SCENE
#include <utilies/shader.h>
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "GlobalVariable.h"
#include "SkyBox.h"
#include <sstream>
#include <fstream>


class Scene {
public:
	vector<GameObject> ices;
	vector<GameObject> obstacles;
	SkyBox* skybox;
	Scene();
	~Scene();
	void createIces(int number);
	void createLadder();
	void createSkybox(std::string cubemapName1, std::string cubemapName2, std::string shaderName);
	void Draw(Shader &shader, bool isShadow);
	void Update(float time);
	void loadGameObject(std::string filename);

private:
	void getPosOrSize(std::string str, float &x, float &y, float& z);

	float rate;

};


#endif // !SCENE
