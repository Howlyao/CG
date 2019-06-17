#pragma once
#ifndef GAME_H
#define GAME_H
#include "GlobalVariable.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include "Player.h"
#include "Sea.h"
#include "TextRenderer.h"

enum GameState {
	GAME_ACTIVE,
	GAME_PAUSE,
	GAME_WIN,
	GAME_OVER,
	GAME_EDIT
};

class Game
{
public:
	// 游戏状态
	GameState  State;
	bool  Keys[1024];
	bool  KeysProcessed[1024];
	int   Width, Height;
	float Time;
	// 构造函数/析构函数
	Game(int width, int height);
	~Game();
	// 初始化游戏状态（加载所有的着色器/纹理）
	void Init();
	// 游戏循环
	void ProcessInput(float dt);
	void ProcessMouseMovement(float offset);
	void Update(float dt);
	void Render();
	void DoCollisions();
	bool CheckCollisionAABB(GameObject &one, GameObject &two);
	bool CheckCollisionOBB(GameObject &one, GameObject &two);
	bool CheckCollisionY(GameObject &one, GameObject &two);
	unsigned int quadVAO = 0;
	Shader shader;

private:
	void renderScene(bool isShadow);


	void renderQuad() {
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			unsigned int quadVBO;
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}

		shader.use();
		shader.setInt("depthMap", 0);
		shader.setFloat("near_plane", 1.0f);
		shader.setFloat("far_plane", 7.5f);
		unsigned int tex = ResourceManager::GetTexture("depthMap");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);	// use the color attachment texture as the texture of the quad plane
		glBindVertexArray(quadVAO);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}


	void lightUpdate(float time);
	

	
};

#endif