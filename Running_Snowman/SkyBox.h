#pragma once
#ifndef SKY_BOX_H
#define SKY_BOX_H
#include "GlobalVariable.h"

class SkyBox {
public:
	SkyBox(std::string cubemapName1, std::string cubemapName2, std::string shaderName);
	void init();
	void Draw(float rate);

private:
	std::string  cubemapName1;
	std::string  cubemapName2;
	std::string shaderName;
	unsigned int skyboxVAO, skyboxVBO;


};

#endif