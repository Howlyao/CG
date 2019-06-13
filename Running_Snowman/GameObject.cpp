#include "GameObject.h"


GameObject::GameObject()
	: position(0.0f, 0.0f, 0.0f), size(1.0f, 1.0f, 1.0f) ,rotation(0.0f), modelName(""), destroyed(false), scale(1.0f, 1.0f, 1.0f) { }

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, float rotation, std::string modelName)
	: position(pos), size(size), rotation(rotation),modelName(modelName), destroyed(false), scale(1.0f, 1.0f, 1.0f){
	
	extents[0] = size.x / 2;
	extents[1] = size.z / 2;
	axes[0] = glm::vec2(cos(glm::radians(-rotation)), sin(glm::radians(-rotation)));
	axes[1] = glm::vec2(-sin(glm::radians(-rotation)),cos(glm::radians(-rotation)));

}

void GameObject::Draw(Shader& shader, bool isShadow)
{	
	SpriteRenderer::RenderSprite(shader, ResourceManager::GetModel(modelName), isShadow ,this->position, scale, this->rotation);
}

float GameObject::getProjectionRadius(glm::vec2 &axis) {
	return extents[0] * fabs(glm::dot(axis, axes[0])) + extents[1] * fabs(glm::dot(axis, axes[1]));
}