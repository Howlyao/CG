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

#endif // ! GLOBAL_VARIABLE




