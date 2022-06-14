#include "Mesh.h"

Mesh::Mesh()
	:vertexArrayObject(NULL),
	vertexBufferObject(NULL),
	indexBufferObject(NULL),
	verticesCount(0),
	indicesCount(0),
	uModel(NULL),
	program(NULL),
	vertices(NULL),
	indices(NULL)
{}

void Mesh::create(float* vertices,uint32_t verticesCount, uint32_t* indices, uint32_t indicesCount,uint32_t shaderProgram)
{
	this->vertices = vertices;
	this->verticesCount = verticesCount;
	this->indicesCount = indicesCount;
	this->indices = indices;
	this->program = shaderProgram;

	//this->texture = Texture(program);
	//this->texture = Texture(program, texturePath);
	//this->texture.create(texturePath);

	/*Creating and Binding Vertex Array Object*/
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	/*Creating and Binding Vertex Buffer Object*/
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, this->verticesCount*sizeof(float), vertices, GL_STATIC_DRAW);

	/*Enable and Setup Vertex Attribute Pointer*/

	//for position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//for normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//for texture Coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/*creating and binding Index Buffer Object*/
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount*sizeof(uint32_t), indices, GL_STATIC_DRAW);


	/*unbinding VAO,VBO, and IBO*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//getting uniform location
	uModel = glGetUniformLocation(program, "model");
	
}

void Mesh::update(glm::mat4* modelMatrix )
{
	glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(*modelMatrix));
}

void Mesh::render()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	//texture.Activate(GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES,indicesCount, GL_UNSIGNED_INT,0);
}
