#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "GlobalVariable.h"
#include "GameObject.h"

class Player : public GameObject{
public:

	const float SPEED = 50.5f;
	const float MouseSensitivity = 0.1f;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	
	float snowmanHeight = 5.0f;
	float decSpeed = 0.05f;

	Player();
	Player(glm::vec3 pos, glm::vec3 size, float rotation, std::string modelName);
	void Move(Movement direction, float dt);
	void Rotate();
	void Draw(Shader& shader, bool isShadow);
	void Update(float dt);
	
	

};

#endif // !PLAYER
