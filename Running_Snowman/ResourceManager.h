#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <utilies\shader.h>
#include <utilies\model.h>
#include "stb_image.h"

/*	Resource Manager
	load Shader and Texture
*/
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader> Shaders;
	// Model storage
	static std::map<std::string, Model> Models;
	// Frame Buffer
	static std::map<std::string, unsigned int> FrameBuffers;
	// Texture storage
	static std::map<std::string, unsigned int> Textures;
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader&   LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	// Retrieves a stored shader
	static Shader&   GetShader(std::string name);
	// Loads Model
	static Model& LoadModel(const char *modelFile, std::string name);
	// Retrieves a stored model
	static Model& GetModel(std::string name);
	// Get FrameBuffer 
	static unsigned int GetFrameBuffer(std::string name);
	//create FrameBuffer and return Texture id
	static unsigned int CreateFrameBuffer(std::string name, int width, int height);
	//
	static unsigned int CreateFrameBufferCube(std::string name, int width, int height);
	//
	static unsigned int LoadTexture(unsigned int texture_id, std::string name);
	//
	static unsigned int LoadTexture(const char *textureFile, std::string name);
	//
	static unsigned int GetTexture(std::string name);
	//
	static unsigned int LoadCubemap(vector<std::string> &faces, std::string name);

	static void      Clear();
private:
	// Private constructor
	ResourceManager() { }

	static unsigned int loadTexture(const char* path);

	static unsigned int loadCubemap(vector<std::string> &faces);
};



#endif