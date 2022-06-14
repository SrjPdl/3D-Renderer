#pragma once
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Texture.h"

class Mesh
{
	private:
		uint32_t vertexArrayObject;
		uint32_t vertexBufferObject;
		uint32_t indexBufferObject;
		uint32_t verticesCount;
		uint32_t indicesCount;
		uint32_t uModel;
		uint32_t program;
		float* vertices;
		uint32_t* indices;
		//Texture texture;

	public:
		Mesh();

		void create(float* vertices, uint32_t verticesCount, uint32_t* indices, uint32_t indicesCount, uint32_t shaderProgram);
		void update(glm::mat4* modelMatrix);
		void render();


};

