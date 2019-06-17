#pragma once
#ifndef GLOBAL_VARIABLE
#define GLOBAL_VARIABLE
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "camera.h"


#include <imgui/imconfig.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>
#include <imgui/imstb_rectpack.h>
#include <imgui/imstb_textedit.h>
#include <imgui/imstb_truetype.h>


using std::cout;
using std::endl;
using std::vector;

extern GLFWwindow* window;

extern glm::mat4 view;
extern glm::mat4 projection;

// settings
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

//MoveSpeed
extern float MoveSpeed;

// camera
extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;

// timing
extern float deltaTime;
extern float lastFrame;


extern glm::vec3 lightPos;
extern glm::vec3 lightDirection;
extern glm::vec3 lightColor;
extern glm::vec3 lightAmbient;
extern glm::vec3 lightDiffuse;
extern glm::vec3 lightSpecular;

//boundary
//extern float border_left;
//extern float border_right;
//extern float border_front;
//extern float border_back;

extern glm::vec3 playerPos;
extern glm::vec3 playerSize;

//ice
extern glm::vec3 iceSize;
extern float iceRangeX;
extern float iceRangeZ;

//ladder
extern glm::vec3 ladderSize;


//day and night
extern float oneDayTime;
extern float dayLeft;
extern float dayRight;
extern float nightLeft;
extern float nightRight;
#endif // ! GLOBAL_VARIABLE


// keyboard
extern vector<bool> isKeyProcessed;

// ImGui
extern const int IMGUI_VIEW_FREEZE;
extern const int IMGUI_VIEW_MOVE;
extern int imgui_view;


extern const int WITH_SHADOW;
extern const int WITHOUT_SHADOW;
extern int shadow_show;

extern const int WITH_PARTICLE;
extern const int WITHOUT_PARTICLE;
extern int particle_show;

extern const int WITH_STENCIL;
extern const int WITHOUT_STENCIL;
extern int stencil_show;


extern const int BLOOD_LOOSE;
extern const int BLOOD_LOCK;
extern int blood_lock;

extern float time_rate;


