#pragma once
#include "GlobalVariable.h"
#include <utilies/shader.h>
class Sea {
private:

	const float PI = 3.14159265359;

	Shader shader = Shader("resources/shaders/waterWave/wave.vs", "resources/shaders/waterWave/waterWave.fs");
	//Shader shader = Shader("resources/shaders/waterWave/wave.vs", "resources/shaders/waterWave/wave.fs");

	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;

	unsigned int VAO, VBO, EBO;
	unsigned int indexCount;

	std::vector<unsigned int> indices;
	
	int waveCount = 2;
	double waveLength[4] = { 0.2, 0.6, 1.2, 2.1 };	//²¨³¤
	double speed[4] = { 0.2,0.5,0.05, 0.02 };	//²¨ËÙ

	glm::vec2 direction[4] = {
		glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.5, 0.9),
		glm::vec2(1.0, 1.0),
	};

	double amplitude[4] = {  //²¨·ù
		0.02,0.02,0.02, 0.01
	};


	double steepness[4]{
		3.0, 1.0, 1.5, 3.0
	};
	// set color
	glm::vec3 seaColor = glm::vec3(0.31, 0.47, 0.75);
	//glm::vec3 seaColor = glm::vec3(0.0, 0.0, 0.75);

public:
	Sea() {
		initGerstnerWave();
		initShader();

	}


	void initGerstnerWave() {

		bool oddRow = false;
		for (int y = 0; y < Y_SEGMENTS - 1; ++y)
		{
			if (!oddRow) // even rows: y == 0, y == 2; and so on
			{
				for (int x = 0; x < X_SEGMENTS; ++x)
				{
					indices.push_back(y       * (X_SEGMENTS)+x);
					indices.push_back((y + 1) * (X_SEGMENTS)+x);
				}
			}
			else
			{
				for (int x = X_SEGMENTS - 1; x >= 0; --x)
				{
					indices.push_back((y + 1) * (X_SEGMENTS)+x);
					indices.push_back(y       * (X_SEGMENTS)+x);
				}
			}
			oddRow = !oddRow;
		}
		indexCount = indices.size();

		vector<float> pos_;
		for (unsigned int x = 0; x < X_SEGMENTS; ++x)
		{
			for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
			{

				float xPos = float((float)x / X_SEGMENTS);
				float yPos = float((float)y / Y_SEGMENTS);
				float zPos = 0.0f;

				pos_.push_back(xPos);
				pos_.push_back(yPos);
				pos_.push_back(zPos);


			}
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, (X_SEGMENTS * Y_SEGMENTS * 3) * sizeof(float), &pos_[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindVertexArray(0);

	}

	void Draw() {
		
		glBindVertexArray(VAO);
		
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setVec3("viewPos", camera.Position);

		float t = glfwGetTime();
		shader.setFloat("t", t);
		glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);


	}


	void initShader() {
		shader.use();
		for (int i = 0; i < waveCount; i++) {
			char str[40];
			sprintf_s(str, "direction[%d]", i);
			shader.setVec2(str, direction[i]);

		}


		for (int i = 0; i < waveCount; i++) {
			char str[40];
			sprintf_s(str, "amplitude[%d]", i);
			shader.setFloat(str, amplitude[i]);

		}

		for (int i = 0; i < waveCount; i++) {
			char str[40];
			sprintf_s(str, "waveLength[%d]", i);
			shader.setFloat(str, waveLength[i]);
		}

		for (int i = 0; i < waveCount; i++) {
			char str[40];
			sprintf_s(str, "speed[%d]", i);
			shader.setFloat(str, speed[i]);
		}

		shader.setFloat("PI", PI);
		//model
		glm::mat4 model = glm::mat4(1.0f);

		//scale
		model = glm::translate(model, glm::vec3(-500.0f, -10.0f, -100.0f));
		model = glm::scale(model, glm::vec3(2000.0f, 150.0f, 2000.0f));

		shader.setMat4("model", model);
		
		//set light
		shader.setVec3("dirLight.direction", lightDirection);
		shader.setVec3("dirLight.color", lightColor);
		shader.setVec3("dirLight.ambient", lightAmbient);
		shader.setVec3("dirLight.diffuse", lightDiffuse);
		shader.setVec3("dirLight.specular", lightSpecular);

		//set color
		shader.setVec3("objectColor", seaColor);	

		////pbr
		//shader.setVec3("albedo", seaColor);
		//shader.setFloat("ao", 1.0f);
		//shader.setVec3("lightPos", glm::vec3(20.0f, 10.0f, 300.0f));
		//shader.setVec3("lightColor", lightColor);
		//shader.setVec3("lightColor", glm::vec3(1000.0f,1000.0f,1000.0f));
		//shader.setFloat("metallic", 0.2f);
		//shader.setFloat("roughness", 0.0f);
		
	}





};