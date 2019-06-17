#include "GlobalVariable.h"

GLFWwindow* window = NULL;

glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// speed
float MoveSpeed = 30.5f;

// camera
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


glm::vec3 lightPos = glm::vec3(0.0f, 100.0f, 0.0f);
glm::vec3 lightDirection = glm::vec3(-1.0, -1.0, -1.0);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 lightAmbient = glm::vec3(0.8f, 0.8f, 0.8f);
glm::vec3 lightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 lightSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
//boundary
//float border_left = -230.0f;
//float border_right = 208.0f;
//float border_front = -230.0f;
//float border_back = 225.0f;

//player
glm::vec3 playerPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 playerSize = glm::vec3(5.0f, 8.0f, 5.0f);

//ice
glm::vec3 iceSize = glm::vec3(5.6f, 1.8f, 5.3f);
float iceRangeX = 210.0f;
float iceRangeZ = 220.0f;

//ladder
glm::vec3 ladderSize = glm::vec3(3.0f, 1.0f, 3.0f);


//day and night
float oneDayTime = 60.0f * 2;
float dayLeft = 20.0 * 2;
float dayRight = 30.0f * 2;
float nightLeft = 50.0f * 2;
float nightRight = 60.0f * 2;


//Menu

// keyboard
vector<bool> isKeyProcessed(1024, false);

// ImGui
const int IMGUI_VIEW_FREEZE = 0;
const int IMGUI_VIEW_MOVE = 1;
int imgui_view = IMGUI_VIEW_MOVE;


const int WITH_SHADOW = 0;
const int WITHOUT_SHADOW = 1;
int shadow_show = WITHOUT_SHADOW;

const int WITH_PARTICLE = 0;
const int WITHOUT_PARTICLE = 1;
int particle_show = WITHOUT_PARTICLE;

const int WITH_STENCIL = 0;
const int WITHOUT_STENCIL = 1;
int stencil_show = WITHOUT_STENCIL;


const int BLOOD_LOOSE = 0;
const int BLOOD_LOCK = 1;
int blood_lock = BLOOD_LOOSE;

float time_rate = 1.0f;
