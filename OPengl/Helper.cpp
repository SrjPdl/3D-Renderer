#include "Helper.h"

void Helper::calculateVertexNormal(float* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount, uint32_t vertexLength, uint32_t normalOffset)
{
	for (uint32_t i = 0; i < indexCount; i+=3)
	{

		uint32_t positionLocation[3] = {
											indices[i] * vertexLength,
											indices[i + 1] * vertexLength,
											indices[i + 2] * vertexLength

									   };

		glm::vec3 firstPoint = glm::vec3(
											vertices[positionLocation[0]],
											vertices[positionLocation[0] + 1],
											vertices[positionLocation[0] + 2]
										);

		glm::vec3 secondPoint = glm::vec3(
											vertices[positionLocation[1]],
											vertices[positionLocation[1] + 1],
											vertices[positionLocation[1] + 2]
										);

		glm::vec3 thirdPoint = glm::vec3(
											vertices[positionLocation[2]],
											vertices[positionLocation[2] + 1],
											vertices[positionLocation[2] + 2]
										);

		glm::vec3 vec1 = glm::vec3(secondPoint - firstPoint);
		glm::vec3 vec2 = glm::vec3(thirdPoint - firstPoint);

		glm::vec3 normal = glm::cross(vec1, vec2);
		normal = glm::normalize(normal);
		
		uint32_t normalLocation[3] = { 0 };
		for (uint32_t i = 0; i < 3; i++)
		{
			normalLocation[i] =positionLocation[i] + normalOffset;

			vertices[normalLocation[i]] += normal.x;
			vertices[normalLocation[i] + 1] += normal.y;
			vertices[normalLocation[i] + 2] += normal.z;
		}

	}

	for (uint32_t i = 0; i < vertexCount; i+=vertexLength)
		{
			glm::vec3 tempNormal = glm::vec3(
												vertices[i + normalOffset],
												vertices[i + normalOffset + 1],
												vertices[i + normalOffset + 2]
											);
		
			tempNormal = glm::normalize(tempNormal);

			vertices[i + normalOffset] = tempNormal.x;
			vertices[i + normalOffset + 1] = tempNormal.y;
			vertices[i + normalOffset + 2] = tempNormal.z;

		}

}
