#include "Scene.h"

Scene::Scene() {
	
}

Scene::~Scene() {
	ices.clear();
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



void Scene::Draw(Shader &shader, bool isShadow) {
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel("scene"), isShadow);

	for (GameObject &ice : ices) {
		if (!ice.destroyed) {
			ice.Draw(shader, isShadow);
		}
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