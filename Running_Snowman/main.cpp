#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <iostream>
#include "Game.h"
#include "GlobalVariable.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

Game *game = new Game(SCR_WIDTH, SCR_HEIGHT);


int main() {

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//MSAA
	//glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_PROGRAM_POINT_SIZE);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_CULL_FACE);
	// load shader

	game->Init();
	
	while (!glfwWindowShouldClose(window)) {

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// key callback
		// -----
		processInput(window);


		game->ProcessInput(deltaTime);
		
		game->Update(deltaTime);
		
		
		game->Render();

	

	
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();


	}

	delete game;

	glfwTerminate();
	return 0;



}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		game->Keys[GLFW_KEY_W] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		game->Keys[GLFW_KEY_S] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		game->Keys[GLFW_KEY_A] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		game->Keys[GLFW_KEY_D] = true;
	}

	

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
		game->Keys[GLFW_KEY_W] = false;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
		game->Keys[GLFW_KEY_S] = false;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
		game->Keys[GLFW_KEY_A] = false;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
		game->Keys[GLFW_KEY_D] = false;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		game->Keys[GLFW_KEY_SPACE] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		game->Keys[GLFW_KEY_SPACE] = false;
	}




	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !game->KeysProcessed[GLFW_KEY_ESCAPE]) {
		game->Keys[GLFW_KEY_ESCAPE] = !game->Keys[GLFW_KEY_ESCAPE];
		game->KeysProcessed[GLFW_KEY_ESCAPE] = true;
	}*/

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		game->KeysProcessed[GLFW_KEY_ESCAPE] = false;
	}

	
	

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;


	if (game->State == GAME_ACTIVE) {
		camera.ProcessMouseMovement(xoffset, yoffset);
		game->ProcessMouseMovement(xoffset);
	}
	
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (game->State == GAME_ACTIVE) {
		camera.ProcessMouseScroll(yoffset);
	}
}




