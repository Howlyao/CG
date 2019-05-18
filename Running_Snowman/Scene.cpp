#include "Scene.h"

Scene::Scene() {
	ices.clear();
	ladders.clear();
	createLadder();
}

Scene::~Scene() {
	
}

void Scene::createIces(int number) {
	std::string modelName = "ice";
	float rotation = 0.0f;
	for (int i = 0; i < number; i++) {
		float posX = 2 * iceRangeX * (float(rand()) / RAND_MAX) - iceRangeX;
		float posZ = 2 * iceRangeZ * (float(rand()) / RAND_MAX) - iceRangeZ;
		glm::vec3 pos = glm::vec3(posX, 0.0f, posZ);
		ices.push_back(GameObject(pos, iceSize, rotation, modelName));
	}

	

}

void Scene::createLadder() {
	std::string modelName = "ladder";
	glm::vec3 pos[12] = {
		glm::vec3(120.0f, 29.032f, 35.0f),
		glm::vec3(123.471, 26.305, 27.466),
		glm::vec3(131.422, 23.578, 25.112),
		glm::vec3(138.388, 20.85, 29.609),
		glm::vec3(139.577, 18.123, 37.813),
		glm::vec3(134.145, 15.396, 44.074),
		glm::vec3(125.855, 12.669, 44.074),
		glm::vec3(120.423, 9.941, 37.813),
		glm::vec3(121.612, 7.214, 29.609),
		glm::vec3(128.578, 4.487, 25.112),
		glm::vec3(136.529, 1.76, 27.466),
		glm::vec3(140.0, -0.968, 35.0)

	};

	float rotation = 0.0f;
	
	for (int i = 11; i > 0; i--) {
		ladders.push_back(GameObject(pos[i], ladderSize, rotation, modelName));
	}
	glm::vec3 size = ladderSize;
	size.y = 5.0f;
	ladders.push_back(GameObject(pos[0], size, rotation, modelName));
}



void Scene::Draw(Shader &shader, bool isShadow) {
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel("scene"), isShadow);
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel("qq"), isShadow, glm::vec3(120.0f, 30.0, 35.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), 150.0f);
	for (GameObject &ice : ices) {
		if (!ice.destroyed) {
			ice.Draw(shader, isShadow);
		}
	}


	for (GameObject &ladder : ladders) {
		ladder.Draw(shader, isShadow);
	}
}

void Scene::Update() {
	for (GameObject &ice : ices) {
		if (ice.destroyed) {
			float posX = 2 * iceRangeX * (float(rand()) / RAND_MAX) - iceRangeX;
			float posZ = 2 * iceRangeZ * (float(rand()) / RAND_MAX) - iceRangeZ;
			ice.position = glm::vec3(posX, 0.0f, posZ);
			ice.destroyed = false;
		}
	}


}
