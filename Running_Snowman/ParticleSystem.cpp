#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int number) {
	this->number = number;
	initParticleSystem();
	
}

ParticleSystem::ParticleSystem(int number, glm::vec3 genPosition, float range_x, float range_z, float skyHeight) {
	this->number = number;
	this->particlesGenPos = genPosition;
	this->range_x = range_x;
	this->range_z = range_z;
	this->skyHeight = skyHeight;

	initParticleSystem();
	
}

void ParticleSystem::initParticleSystem() {
	snowTexture = ResourceManager::GetTexture("snow");
	particles.resize(number);
	initParticleVAO();
	
	for (Particle &particle : particles) {
		respawnParticle(particle);
	}

}

void ParticleSystem::initParticleVAO() {
	GLuint VBO;
	GLfloat particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(float)));
	glBindVertexArray(0);
}



void ParticleSystem::respawnParticle(Particle &particle) {
	//初始化颜色（白色）
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
	particle.color = glm::vec4(r, g, b, a);

	//初始化坐标
	x = range_x * (rand() / float(RAND_MAX)) - range_x / 2;
	z = range_z * (rand() / float(RAND_MAX)) - range_z / 2;
	y = skyHeight;
	particle.position = glm::vec3(x, y, z);

	//初始化速度
	vx = rand() / float(RAND_MAX) * VELOCITY_X_MAX;
	vy = rand() / float(RAND_MAX) * (VELOCITY_Y_MAX - VELOCITY_Y_MIN) + VELOCITY_Y_MIN;
	vz = 0;
	particle.velocity = glm::vec3(vx, vy, vz);


	//旋转角度
	rx = (rand() / float(RAND_MAX)) * ROTATE_ANGLE_MAX;
	ry = (rand() / float(RAND_MAX))  * ROTATE_ANGLE_MAX;
	//旋转速度
	rv = rand() / float(RAND_MAX) * ROTATE_VELOCITY;

	particle.rotateAngle = glm::vec2(rx, ry);
	particle.rotateSpeed = rv;

	//初始化加速度
	ax = 0;
	ay = G_ACCE;
	az = 0;
	particle.acceleration = glm::vec3(ax, ay, az);

	//初始化生命周期
	particle.lifetime = LIFE_TIME;

	//消失速度
	dec = rand() / float(RAND_MAX) * DEC_MAX;
	particle.dec = dec;

	//初始化大小
	particle.scale = rand() / float(RAND_MAX) * (SCALE_MAX - SCALE_MIN) + SCALE_MIN;

}




void ParticleSystem::Update(float dt) {

	for (Particle &particle : particles) {
		/** 更新位置 */
		position = particle.position;
		velocity = particle.velocity;
		acceleration = particle.acceleration;
		lifetime = particle.lifetime;
		dec = particle.dec;

		position.x += velocity.x;
		position.y -= velocity.y;
		// velocity.y *dt * DT_SCALE

		/** 更新速度 */
		velocity.y += acceleration.y * dt * DT_SCALE;

		/** 更新生存时间 */
		lifetime -= dec * dt * DT_SCALE;

		/** 如果粒子消失或生命结束 */
		if (position.y <= -1 || lifetime <= 0)
		{
			respawnParticle(particle);
			return;


		}

		particle.position = position;
		particle.velocity = velocity;
		particle.acceleration = acceleration;
		particle.lifetime = lifetime;
		particle.dec = dec;

	}
	setGenPos(camera.Position);

}

void ParticleSystem::Draw(Shader& shader) {
	shader.use();
	/*projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();*/
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, snowTexture);
	for (Particle &particle : particles) {
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, particle.position);
		model = glm::translate(model, particlesGenPos);
		model = glm::rotate(model, glm::radians(particle.rotateAngle.x * particle.rotateSpeed * (float)glfwGetTime()), glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, glm::radians(particle.rotateAngle.y * particle.rotateSpeed * (float)glfwGetTime()), glm::vec3(0.0, 1.0, 0.0));
		shader.setMat4("model", model);
		shader.setVec4("color", particle.color);
		shader.setFloat("scale", particle.scale);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
	glBindVertexArray(0);

}

void ParticleSystem::setGenPos(glm::vec3 pos) {
	this->particlesGenPos = pos;

}