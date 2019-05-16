#pragma once
#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H
#include <cmath>
#include "GlobalVariable.h"
#include <iostream>
#include <vector>

#include "ResourceManager.h"
using std::vector;

struct Particle {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	glm::vec2 rotateAngle;
	float rotateSpeed;
	float lifetime;
	float scale;
	float dec;

	Particle()
		: position(0.0f), velocity(0.0f), color(1.0f), lifetime(1.0f), scale(1.0f), acceleration(1.0f), dec(1.0f), rotateAngle(0.0f), rotateSpeed(0.0f) { }
};


class ParticleSystem {
private:
	glm::vec3 particlesGenPos;
	float range_x, range_z, skyHeight;
	int number;

	const float DT_SCALE = 100.0f;
	const float LIFE_TIME = 100.0f;
	const float VELOCITY_X_MAX = 0.01f;
	const float VELOCITY_Y_MIN = 0.05f;
	const float VELOCITY_Y_MAX = 0.1f;
	const float ROTATE_ANGLE_MAX = 360.0f;
	const float ROTATE_VELOCITY = 0.001f;
	const float G_ACCE = 0.000005f;
	const float DEC_MAX = 0.05f;
	const float SCALE_MIN = 0.05f;
	const float SCALE_MAX = 0.1f;
	vector<Particle> particles;

	float x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec, rx, ry, rv;
	float r, g, b, a;
	glm::vec3 position, velocity, acceleration, scale;

	unsigned int VAO;
	unsigned int snowTexture;
public:
	ParticleSystem(int number);
	ParticleSystem(int number, glm::vec3 genPosition, float range_x, float range_z, float skyHeight);
	void initParticleVAO();
	void initParticleSystem();

	void respawnParticle(Particle &particle);
	void Update(float dt);
	void Draw(Shader &shader);
	void setGenPos(glm::vec3 pos);
	
};

#endif