#pragma once
#ifndef SCENE
#define SCENE
#include <utilies/shader.h>
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "GlobalVariable.h"
class Scene {
public:
	vector<GameObject> ices;
	Scene();
	~Scene();
	void createIces(int number);
	void Draw(Shader &shader, bool isShadow);
	void Update();

};


#endif // !SCENE
