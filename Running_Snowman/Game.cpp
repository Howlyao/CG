#include "Game.h"


Scene *scene = NULL;
ParticleSystem *particleSystem = NULL;
Player *player = NULL;
Sea *sea = NULL;

Game::Game(int width,int height) {
	this->Width = width;
	this->Height = height;
	
	//initial Key to false
	memset(Keys, false, sizeof(Keys));
	memset(KeysProcessed, false, sizeof(KeysProcessed));
	
}

Game::~Game() {
	delete scene;
	delete particleSystem;
	delete player;
	delete sea;

}

void Game::Init() {
	//shader = Shader("resources/shaders/depthShader/test.vs", "resources/shaders/depthShader/test.fs");
	Time = 0.0f;

	this->State = GAME_ACTIVE;
	// load model
	ResourceManager::LoadModel("resources/models/scene/scene.obj", "scene");
	//ResourceManager::LoadModel("E:/homework/CG/3dsmax/scene2/scene.obj", "scene");
	//ResourceManager::LoadModel("F:/Scene/scene.obj", "scene");
	ResourceManager::LoadModel("resources/models/snowman/snowman.obj", "snowman");
	ResourceManager::LoadModel("resources/models/QQ/qq.obj", "qq");
	ResourceManager::LoadModel("resources/models/ice/ice.obj", "ice");
	ResourceManager::LoadModel("resources/models/ladder/ladder.obj", "ladder");
	ResourceManager::LoadModel("resources/models/hp/hp.obj", "hp");
	ResourceManager::LoadModel("resources/models/wall/wall.obj", "wall");
	
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMap = ResourceManager::CreateFrameBuffer("depthFBO", SHADOW_WIDTH, SHADOW_HEIGHT);
	ResourceManager::LoadTexture(depthMap, "depthMap");

	unsigned int depthCubemap = ResourceManager::CreateFrameBufferCube("pointDepthFBO", SHADOW_WIDTH, SHADOW_HEIGHT);
	ResourceManager::LoadTexture(depthCubemap, "depthCubemap");
	
	// load shader
	Shader depthShader = ResourceManager::LoadShader("resources/shaders/depthShader/depthShader.vs", "resources/shaders/depthShader/depthShader.fs", NULL, "depthShader");
	Shader pointDepthShader = ResourceManager::LoadShader("resources/shaders/depthShader/pointDepthShader.vs", "resources/shaders/depthShader/pointDepthShader.fs", "resources/shaders/depthShader/pointDepthShader.gs", "pointDepthShader");
	Shader lightShader = ResourceManager::LoadShader("resources/shaders/lightShader/lightShader.vs", "resources/shaders/lightShader/lightShader.fs", NULL, "lightShader");
	Shader pointLightShader = ResourceManager::LoadShader("resources/shaders/lightShader/pointLightShader.vs", "resources/shaders/lightShader/pointLightShader.fs", NULL, "pointLightShader");
	Shader snowShader = ResourceManager::LoadShader("resources/shaders/snow/snow.vs", "resources/shaders/snow/snow.fs", NULL, "snowShader");
	Shader snowmanShader = ResourceManager::LoadShader("resources/shaders/snowman/snowman.vs", "resources/shaders/snowman/snowman.fs", NULL, "snowmanShader");
	Shader stencilShader = ResourceManager::LoadShader("resources/shaders/stencil/stencil.vs", "resources/shaders/stencil/stencil.fs", NULL, "stencilShader");
	Shader hpShader = ResourceManager::LoadShader("resources/shaders/hpShader/hp.vs", "resources/shaders/hpShader/hp.fs", NULL, "hpShader");
	Shader skyboxShader = ResourceManager::LoadShader("resources/shaders/skybox/skybox.vs", "resources/shaders/skybox/skybox.fs", NULL, "skyboxShader");
	
	// get shader
	
	//load Texture
	unsigned int snowTexture = ResourceManager::LoadTexture("resources/textures/particles/snow.png", "snow");
	
	//load skyBox
	vector<std::string> faces1
	{
		"resources/textures/skybox/skybox4/right.jpg",
		"resources/textures/skybox/skybox4/left.jpg",
		"resources/textures/skybox/skybox4/top.jpg",
		"resources/textures/skybox/skybox4/bottom.jpg",
		"resources/textures/skybox/skybox4/front.jpg",
		"resources/textures/skybox/skybox4/back.jpg"
	};

	

	vector<std::string> faces2
	{
		"resources/textures/skybox/skybox3/right.bmp",
		"resources/textures/skybox/skybox3/left.bmp",
		"resources/textures/skybox/skybox3/top.bmp",
		"resources/textures/skybox/skybox3/bottom.bmp",
		"resources/textures/skybox/skybox3/front.bmp",
		"resources/textures/skybox/skybox3/back.bmp"
	};
	unsigned int cubemapTexture1 = ResourceManager::LoadCubemap(faces1, "skybox1");
	unsigned int cubemapTexture2 = ResourceManager::LoadCubemap(faces2, "skybox2");

	// Set Shader Texture
	lightShader.use();
	lightShader.setInt("depthMap", 6);
	pointLightShader.use();
	pointLightShader.setInt("depthMap", 6);
	snowShader.use();
	snowShader.setInt("snowTexture", 0);
	skyboxShader.use();
	skyboxShader.setInt("skybox1", 0);
	skyboxShader.setInt("skybox2", 1);
	
	// set direct light space matrix
	//float near_plane = 1.0f, far_plane = 100.0f;
	//glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	//glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	//glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	//depthShader.use();
	//depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
	//lightShader.use();
	//lightShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
	//lightShader.setVec3("dirLight.direction", lightDirection);
	//lightShader.setVec3("dirLight.color", lightColor);
	//lightShader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	//lightShader.setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	//lightShader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	// set point light shader
	float near_plane = 1.0f;
	float far_plane = 1000.0;
	
	pointLightShader.use();
	pointLightShader.setVec3("pointLight.pos", lightPos);
	pointLightShader.setVec3("pointLight.color", lightColor);
	pointLightShader.setVec3("pointLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	pointLightShader.setVec3("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	pointLightShader.setVec3("pointLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	pointLightShader.setFloat("far_plane", far_plane);


	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	
	pointDepthShader.use();
	for (unsigned int i = 0; i < 6; ++i)
		pointDepthShader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
	pointDepthShader.setFloat("far_plane", far_plane);
	pointDepthShader.setVec3("lightPos", lightPos);


	//snowmanShader.use();
	//snowmanShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
	//snowmanShader.setVec3("dirLight.direction", lightDirection);
	//snowmanShader.setVec3("dirLight.color", lightColor);
	//snowmanShader.setVec3("dirLight.ambient", lightAmbient);
	//snowmanShader.setVec3("dirLight.diffuse", lightDiffuse);
	//snowmanShader.setVec3("dirLight.specular", lightSpecular);

	snowmanShader.use();
	snowmanShader.setVec3("pointLight.pos", lightPos);
	snowmanShader.setVec3("pointLight.color", lightColor);
	snowmanShader.setVec3("pointLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	snowmanShader.setVec3("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	snowmanShader.setVec3("pointLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));


	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);
	//
	scene = new Scene();
	scene->createIces(20);
	scene->createLadder();
	scene->createSkybox("skybox1", "skybox2", "skyboxShader");
	scene->loadGameObject("./resources/bounding_box.txt");

	//particle
	particleSystem = new ParticleSystem(100, glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 10.0f);

	//player
	player = new Player(playerPos, playerSize, 0.0f, "snowman");
	glm::vec3 Pos = player->position;
	camera.Position = Pos + glm::vec3(0.0f, 9.0f, 0.0f);
	
	//Sea
	sea = new Sea();
}	

void Game::ProcessInput(float dt) {
	if (this->State == GAME_ACTIVE) {
		if (this->Keys[GLFW_KEY_ESCAPE]) {
			this->State = GAME_PAUSE;
			//show menu
			
		}
		if (this->Keys[GLFW_KEY_W]) {
			player->Move(FORWARD, dt);
		}
		if (this->Keys[GLFW_KEY_S]) {
			player->Move(BACKWARD, dt);
		}
		if (this->Keys[GLFW_KEY_A]) {
			player->Move(LEFT, dt);
		}
		if (this->Keys[GLFW_KEY_D]) {
			player->Move(RIGHT, dt);
		}
		if (this->Keys[GLFW_KEY_SPACE]) {
			player->Jump();
		}





	}
	else if (this->State == GAME_PAUSE) {
		if (this->Keys[GLFW_KEY_ESCAPE]) {
			this->State = GAME_ACTIVE;
		}
	}
}

void Game::ProcessMouseMovement(float offset) {
	player->Rotate();
	
}


void Game::Update(float dt) {
	if (this->State == GAME_ACTIVE) {
		particleSystem->Update(dt);
		
		scene->Update(Time);
		player->Update(dt);
		camera.Update(player->position);
		//cout << player->position.x << " " << player->position.y << " " << player->position.z << endl;
		DoCollisions();
		Time += dt;
	}
}

void Game::Render() {
	if (this->State == GAME_ACTIVE) {
		//Shadow mapping
		renderScene(true);
		//render scene width shadow mapping
		renderScene(false);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glViewport(0, 0, Width, Height);
		// //clear all relevant buffers
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//renderQuad();
		
		
	}
	if (this->State == GAME_PAUSE) {

	}
}

void Game::renderScene(bool isShadow) {



	//ÒõÓ°ÌùÍ¼
	if (isShadow) {

		//unsigned int depthFBO = ResourceManager::GetFrameBuffer("depthFBO");
		//Shader depthShader = ResourceManager::GetShader("depthShader");
		//glEnable(GL_DEPTH_TEST);
		//glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
		//glViewport(0, 0, Width, Height);
		//glClear(GL_DEPTH_BUFFER_BIT);
		//
		//depthShader.use();
		//
	
		//scene->Draw(depthShader, true);
		//player->Draw(depthShader, true);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		glEnable(GL_DEPTH_TEST);
		unsigned int pointDepthFBO = ResourceManager::GetFrameBuffer("pointDepthFBO");
		Shader pointDepthShader = ResourceManager::GetShader("pointDepthShader");
		
		glBindFramebuffer(GL_FRAMEBUFFER, pointDepthFBO);
		glViewport(0, 0, 1024, 1024);
		glClear(GL_DEPTH_BUFFER_BIT);

		pointDepthShader.use();
		scene->Draw(pointDepthShader, true);
		player->Draw(pointDepthShader, true);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		
	}
	else {
		// Load shadow map texture
		//unsigned int depthMap = ResourceManager::GetTexture("depthMap");
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//glActiveTexture(GL_TEXTURE6);
		//glBindTexture(GL_TEXTURE_2D, depthMap);
		

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

		//point
		unsigned int depthCubemap = ResourceManager::GetTexture("depthCubemap");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);


		// Load shader and set uniform variable
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (float)Width / (float)Height, 0.1f, 1000.0f);
		//Shader lightShader = ResourceManager::GetShader("lightShader");
		Shader lightShader = ResourceManager::GetShader("pointLightShader");
		//Player render
		Shader snowmanShader = ResourceManager::GetShader("snowmanShader");
		player->Draw(snowmanShader, false);


		Shader snowShader = ResourceManager::GetShader("snowShader");
		particleSystem->Draw(snowShader);

		sea->Draw();

		scene->Draw(lightShader, false);
	}
}

void Game::DoCollisions() {
	for (GameObject &box : scene->ices)
	{
		if (!box.destroyed)
		{
			if (CheckCollisionOBB(*player, box))
			{
				player->snowmanHeight += 0.05f;
				box.destroyed = true;
			}
		}
	}
	//check collision with ladder
	player->landY = 0.0f;
	for (GameObject &box : scene->obstacles)
	{
		//collision in planeXOZ
		if (CheckCollisionOBB(*player, box))
		{
			
			// player above the ladder
			if (player->position.y + 1.0f > box.position.y + box.size.y) {
				
				player->landY = player->landY > box.position.y + box.size.y ? player->landY : box.position.y + box.size.y;
				//player->isFlying = true;
			} // collision in 3D
			else if (CheckCollisionY(*player, box)){
				
				
				// ¶¥Í·
				if (player->position.y + player->size.y >= box.position.y && player->position.y + player->size.y - box.position.y <= 0.5f) {
					player->velocityY = 0.0f;
					player->position.y = box.position.y - player->size.y;
				}
				else {
					//wrong only for square
					//glm::vec2 nv = glm::normalize(player->centerPoint - box.centerPoint);
					/*if (fabs(nv.x) > fabs(nv.y)) {
						player->position.x = box.position.x + (nv.x / fabs(nv.x) * (box.extents[0] + player->extents[0]));

					}
					else {
						player->position.z = box.position.z + (nv.y / fabs(nv.y) * (box.extents[1] + player->extents[1]));
					}*/

					player->SetCollisionPosition(box);

				}
				
			}
			
		}
	}
	// is isCollision, there is nothing under player

	if (player->landY + 1.0f < player->position.y){
		player->isFlying = true;
	}
}

bool Game::CheckCollisionAABB(GameObject &one, GameObject &two) {
	bool collisionX = one.position.x + one.extents[0] >= two.position.x - two.extents[0] &&
		two.position.x + two.extents[0] >= one.position.x - one.extents[0];
	
	bool collisionY = one.position.y + one.size.y >= two.position.y &&
		two.position.y + two.size.y >= one.position.y;

	bool collisionZ = one.position.z + one.extents[1] >= two.position.z &&
		two.position.z + one.extents[1] >= one.position.z;
	
	return collisionX && collisionY && collisionZ;
}

bool Game::CheckCollisionOBB(GameObject &one, GameObject &two) {
	glm::vec2 nv = glm::vec2(one.position.x, one.position.z) - glm::vec2(two.position.x, two.position.z);
	glm::vec2 axisA1 = one.axes[0];
	if (one.getProjectionRadius(axisA1) + two.getProjectionRadius(axisA1) <= fabs(glm::dot(nv, axisA1)))
		return false;
	glm::vec2 axisA2 = one.axes[1];
	if (one.getProjectionRadius(axisA2) + two.getProjectionRadius(axisA2) <= fabs(glm::dot(nv, axisA2)))
		return false;
	glm::vec2 axisB1 = two.axes[0];
	if (one.getProjectionRadius(axisB1) + two.getProjectionRadius(axisB1) <= fabs(glm::dot(nv, axisB1)))
		return false;
	glm::vec2 axisB2 = two.axes[1];
	if (one.getProjectionRadius(axisB2) + two.getProjectionRadius(axisB2) <= fabs(glm::dot(nv, axisB2)))
		return false;
	
	return true;

}


bool Game::CheckCollisionY(GameObject &one, GameObject &two) {
	bool collisionY = one.position.y + one.size.y > two.position.y &&
		two.position.y + two.size.y > one.position.y;

	return collisionY;
}