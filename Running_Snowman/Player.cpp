#include "Player.h"

Player::Player() : GameObject() {}

Player::Player(glm::vec3 pos, glm::vec3 size, float rotation, std::string modelName) 
: GameObject(pos, size,rotation, modelName) {}

void Player::Move(Movement direction, float dt) {
	// Move the Snowman
	float moveSpeed = this->SPEED * dt;

	if (direction == FORWARD)
		position += front * moveSpeed;
	if (direction == BACKWARD)
		position -= front * moveSpeed;
	if (direction == LEFT)
		position -= right * moveSpeed;
	if (direction == RIGHT)
		position += right * moveSpeed;


	if (this->position.x <= border_left)
	{
		this->position.x = border_left;
	}
	else if (this->position.x >= border_right)
	{
		
		this->position.x = border_right;
	}
	if (this->position.z <= border_front)
	{
		
		this->position.z = border_front;
	}
	else if (this->position.z >= border_back) {
		this->position.z = border_back;
	}
	centerPoint.x = position.x;
	centerPoint.y = position.z;


}

void Player::Jump() {
	isFlying = true;
	velocityY = JumpVelocityY;
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
	glm::vec3 scale = glm::vec3(1.0f);
	shader.use();
	
	shader.setFloat("snowmanHeight", snowmanHeight + position.y);
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel(modelName), isShadow, this->position, scale, this->rotation);
	
}

void Player::Update(float dt) {
	/*float decrement = decSpeed * dt;
	snowmanHeight -= decrement;
	if (snowmanHeight <= 0.0f) {
		snowmanHeight = 0.0f;
	}*/

	if (isFlying)
		Fall(dt);
}