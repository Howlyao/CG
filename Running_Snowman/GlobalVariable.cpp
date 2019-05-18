#include "GlobalVariable.h"

glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


glm::vec3 lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
glm::vec3 lightDirection = glm::vec3(-1.0, -1.0, -1.0);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 lightAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 lightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 lightSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
//boundary
float border_left = -230.0f;
float border_right = 208.0f;
float border_front = -230.0f;
float border_back = 225.0f;

//player
glm::vec3 playerPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 playerSize = glm::vec3(2.5f, 5.0f, 2.5f);

//ice
glm::vec3 iceSize = glm::vec3(2.5f, 2.5f, 0.7f);
float iceRangeX = 210.0f;
float iceRangeZ = 220.0f;

//ladder
glm::vec3 ladderSize = glm::vec3(3.0f, 1.0f, 3.0f);