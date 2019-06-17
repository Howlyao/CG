#include "Player.h"

Player::Player() : GameObject() {}

Player::Player(glm::vec3 pos, glm::vec3 size, float rotation, std::string modelName) 
: GameObject(pos, size,rotation, modelName) {}



void Player::Move(Movement direction, float dt) {
	// Move the Snowman
	float moveSpeed = MoveSpeed * dt;

	if (direction == FORWARD)
		position += front * moveSpeed;
	if (direction == BACKWARD)
		position -= front * moveSpeed;
	if (direction == LEFT)
		position -= right * moveSpeed;
	if (direction == RIGHT)
		position += right * moveSpeed;


	//if (this->position.x <= border_left)
	//{
	//	this->position.x = border_left;
	//}
	//else if (this->position.x >= border_right)
	//{
	//	
	//	this->position.x = border_right;
	//}
	//if (this->position.z <= border_front)
	//{
	//	
	//	this->position.z = border_front;
	//}
	//else if (this->position.z >= border_back) {
	//	this->position.z = border_back;
	//}


	
}



void Player::Jump() {
	if (!isFlying)
		velocityY = JumpVelocityY;
	isFlying = true;
}

void Player::Fall(float dt) {
	position.y += (velocityY * dt + AcceG * dt * dt / 2);
	velocityY += AcceG * dt;
	if (position.y <= landY) {
		position.y = landY;
		velocityY = 0.0f;
		isFlying = false;
	}
	
}

void Player::Rotate() {
	float yaw = camera.Yaw;
	this->rotation = (90.0 + yaw);
	//this->rotation -= offset * MouseSensitivity;
	this->front = camera.front;
	this->right = camera.right;
}

void Player::Draw(Shader& shader, bool isShadow)
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glm::vec3 scale = glm::vec3(1.0f);
	Shader hpShader = ResourceManager::GetShader("hpShader");
	hpShader.use();

	hpShader.setFloat("snowmanHeight", snowmanHeight + position.y);
	
	if (!isShadow) {
		SpriteRenderer::RenderSprite(ResourceManager::GetShader("hpShader"), ResourceManager::GetModel("hp"), isShadow, this->position, scale, this->rotation);
	}
	shader.use();
	shader.setFloat("snowmanHeight", snowmanHeight + position.y);
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel(modelName), isShadow, this->position, scale, this->rotation);
	glDisable(GL_BLEND);
}

void Player::Update(float dt) {

	if (snowmanHeight > 8.0) {
		snowmanHeight = 8.0f;
	}else if (blood_lock == BLOOD_LOOSE) {
		float decrement = decSpeed * dt * time_rate;
		snowmanHeight -= decrement;

	}
	if (snowmanHeight < 0.0f) {
		snowmanHeight = 0.0f;
	}
	
	if (imgui_view == IMGUI_VIEW_MOVE) {
		if (isFlying)
			Fall(dt);
	}
}


void Player::SetCollisionPosition(GameObject &box) {
	float lengthX = 500.0f, lengthZ = 500.0f;
	bool flagX = true, flagZ = true;
	if (this->position.x + this->extents[0] > box.position.x - box.extents[0] &&
		this->position.x - this->extents[0] <= box.position.x - box.extents[0]) {
		
		flagX = true;
		lengthX = this->position.x + this->extents[0] - (box.position.x - box.extents[0]);
		
	}

	else if (this->position.x + this->extents[0] > box.position.x + box.extents[0] &&
		this->position.x - this->extents[0] <= box.position.x + box.extents[0]) {

		flagX = false;
		lengthX = (box.position.x + box.extents[0]) - (this->position.x - this->extents[0]);
		
	}

	//cout << this->position.z + this->extents[1] << " 1 " << box.position.z - box.extents[1] << endl;
	//cout << this->position.z - this->extents[1] << " 2 " << box.position.z + box.extents[1] << endl;


	if (this->position.z + this->extents[1] > box.position.z - box.extents[1] &&
		this->position.z - this->extents[1] <= box.position.z - box.extents[1]) {

		flagZ = true;
		lengthZ = this->position.z + this->extents[1] - (box.position.z - box.extents[1]);
		
	}
	else if (this->position.z + this->extents[1] > box.position.z + box.extents[1] &&
		this->position.z - this->extents[1] <= box.position.z + box.extents[1]) {

		flagZ = false;
		lengthZ = (box.position.z + box.extents[1]) - (this->position.z - this->extents[1]);
		
	}


	
	if (lengthX < lengthZ) {
		if (flagX) {
			this->position.x = box.position.x - box.extents[0] - this->extents[0];
			
		}
		else {
			this->position.x = box.position.x + box.extents[0] + this->extents[0];
			
		}
	}
	else if (lengthX > lengthZ){
		if (flagZ) {
			this->position.z = box.position.z - box.extents[1] - this->extents[1];
			
		}
		else {
			this->position.z = box.position.z + box.extents[1] + this->extents[1];
			
		}
	}
}