#pragma once
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace Helper
{
	void calculateVertexNormal(float* vertices,uint32_t vertexCount, uint32_t* indices, uint32_t indexCount, uint32_t vertexLength, uint32_t normalOffset);
}