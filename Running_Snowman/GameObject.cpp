#include "GameObject.h"


GameObject::GameObject()
	: position(0.0f, 0.0f, 0.0f), size(1.0f, 1.0f, 1.0f) ,rotation(0.0f), modelName(""), destroyed(false) { }

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, float rotation, std::string modelName)
	: position(pos), size(size), rotation(rotation),modelName(modelName), destroyed(false) { }

void GameObject::Draw(Shader& shader, bool isShadow)
{	
	glm::vec3 scale = glm::vec3(1.0f);
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel(modelName), isShadow ,this->position, scale, this->rotation);
}