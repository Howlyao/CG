#include "Scene.h"

Scene::Scene() {
	ices.clear();
	obstacles.clear();
	skybox = NULL;
	this->rate = 0.0f;
	
}

Scene::~Scene() {
	ices.clear();
	obstacles.clear();
	delete skybox;
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
	//std::string modelName = "ladder";
	//glm::vec3 pos[12] = {
	//	glm::vec3(120.0f, 29.032f, 35.0f),
	//	glm::vec3(123.471, 26.305, 27.466),
	//	glm::vec3(131.422, 23.578, 25.112),
	//	glm::vec3(138.388, 20.85, 29.609),
	//	glm::vec3(139.577, 18.123, 37.813),
	//	glm::vec3(134.145, 15.396, 44.074),
	//	glm::vec3(125.855, 12.669, 44.074),
	//	glm::vec3(120.423, 9.941, 37.813),
	//	glm::vec3(121.612, 7.214, 29.609),
	//	glm::vec3(128.578, 4.487, 25.112),
	//	glm::vec3(136.529, 1.76, 27.466),
	//	glm::vec3(140.0, -0.968, 35.0)

	//};

	//float rotation = 0.0f;
	//
	//for (int i = 11; i > 0; i--) {
	//	obstacles.push_back(GameObject(pos[i], ladderSize, rotation, modelName));
	//}
	//glm::vec3 size = ladderSize;
	//size.y = 5.0f;
	//obstacles.push_back(GameObject(pos[0], size, rotation, modelName));

	////wall test collision;
	//glm::vec3 wallSize = glm::vec3(60.0f, 20.0f, 6.0f);
	//obstacles.push_back(GameObject(glm::vec3(10.0f, 0.0f, -10.0f), wallSize, 0.0f, "wall"));

	

}

void Scene::createSkybox(std::string cubemapName1, std::string cubemapName2, std::string shaderName) {
	skybox = new SkyBox(cubemapName1, cubemapName2, shaderName);
}

void Scene::Draw(Shader &shader, bool isShadow) {
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel("scene"), isShadow);
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel("qq"), isShadow, glm::vec3(169.187f, 86.989, 11.958f),
		glm::vec3(1.0f, 1.0f, 1.0f), -120.0f);
	
	
	for (GameObject &ladder : obstacles) {
		ladder.Draw(shader, isShadow);
	}


	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
	glStencilMask(0xFF); // 启用模板缓冲写入
	for (GameObject &ice : ices) {
		if (!ice.destroyed) {
			ice.scale = glm::vec3(1.0f, 1.0f, 1.0f);
			ice.Draw(shader, isShadow);
		}
	}
	
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	if (stencil_show == WITH_STENCIL) {
		if (!isShadow) {
			for (GameObject &ice : ices) {
				if (!ice.destroyed) {
					ice.scale = glm::vec3(1.05f, 1.05f, 1.05f);
					ice.Draw(ResourceManager::GetShader("stencilShader"), isShadow);
				}
			}
		}
	}
	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);


	if (skybox != NULL) {

		skybox->Draw(rate);
	}
}

void Scene::Update(float time) {
	for (GameObject &ice : ices) {
		if (ice.destroyed) {
			float posX = 2 * iceRangeX * (float(rand()) / RAND_MAX) - iceRangeX;
			float posZ = 2 * iceRangeZ * (float(rand()) / RAND_MAX) - iceRangeZ;
			ice.position = glm::vec3(posX, 0.0f, posZ);
			ice.destroyed = false;
		}
	}

	
	time = time - (int)(time / oneDayTime) * oneDayTime;

	if (time < dayLeft) {
		rate = 0.0f;
	}
	else if (time >= dayLeft && time <= dayRight) {
		rate = (time - dayLeft) / (dayRight - dayLeft);
	}
	else if (time > dayRight && time < nightLeft) {
		rate = 1.0f;
	}
	else if (time >= nightLeft && time <= nightRight) {
		rate = 1.0f - ((time - nightLeft) / (nightRight - nightLeft));
	}




}

void Scene::loadGameObject(std::string filename) {
	std::ifstream boundingBoxFile;
	std::string boundingBoxInfo;

	boundingBoxFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		boundingBoxFile.open(filename.c_str());
		std::stringstream bbSstream;
		bbSstream << boundingBoxFile.rdbuf();
		boundingBoxInfo = bbSstream.str();

		std::string str;
		float x, y, z;
		float sizeX, sizeY, sizeZ;
		while (getline(bbSstream, str)) {
			if (strstr(str.c_str(),"ladder") != NULL || strstr(str.c_str(), "Rock") != NULL || 
				strstr(str.c_str(), "Wall") != NULL) {
				getline(bbSstream, str);
				getPosOrSize(str, x, y, z);
				

				getline(bbSstream, str);
				getPosOrSize(str, sizeX, sizeY, sizeZ);

				// make the center point at the bottom
				y -= sizeY / 2;
				z = -z;
				glm::vec3 pos(x, y, z);
				glm::vec3 size(sizeX, sizeY, sizeZ);
				obstacles.push_back(GameObject(pos, size, 0.0f, ""));
				

				//cout << x << " " << y << " " << z << endl;
				//cout << sizeX << " " << sizeY << " " << sizeZ << endl;
				
			}
		}

	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::BOUNDINGBOX::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return;
	}

	boundingBoxFile.close();


}


void Scene::getPosOrSize(std::string str, float &x, float &y, float& z) {
	int start = 0, index;
	str = str.substr(1, str.length() - 2);
	index = str.find(',', start);
	x = atof(str.substr(start, index - start).c_str());
	start = index + 1;
	index = str.find(',', start);
	z = atof(str.substr(start, index - start).c_str());
	start = index + 1;
	y = atof(str.substr(start, str.length() - start).c_str());

	
	//cout << x << " " << y << " " << z << endl;
}