#pragma once
#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utilies/model.h>
#include <utilies/shader.h>


class SpriteRenderer
{
public:
	// Constructor (inits shaders/shapes)
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given model and shader
	static void RenderSprite(Shader &shader, Model &sprite, bool isShadow, glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), float rotate = 0.0f);
private:
	SpriteRenderer();
	
};

#endif