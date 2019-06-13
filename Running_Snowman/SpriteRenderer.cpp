#include "SpriteRenderer.h"
#include "GlobalVariable.h"
SpriteRenderer::SpriteRenderer() {
	
}

void SpriteRenderer::RenderSprite(Shader &shader, Model &sprite, bool isShadow, glm::vec3 position, glm::vec3 scale, float rotate) {
	// Prepare transformations
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)	
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f)); // Then rotate
	model = glm::scale(model, glm::vec3(scale)); // Last scale

	shader.setMat4("model", model);
	if (!isShadow) {
		shader.setMat4("view", view);	//view global variable
		shader.setMat4("projection", projection);  //projection global variable
		shader.setVec3("viewPos", camera.Position);
	}
	sprite.Draw(shader);

}