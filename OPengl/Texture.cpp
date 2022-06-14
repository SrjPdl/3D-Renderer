#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture()
	:data(NULL),
	width(NULL),
	height(NULL),
	channels(NULL),
	texture(NULL),
	program(NULL)
{
}

Texture::Texture(uint32_t shaderProgram, const char* path, uint32_t textureUnit)
	:data(NULL),
	 width(NULL),
	 height(NULL),
	 channels(NULL),
	 texture(NULL),
	 program(shaderProgram),
	 textureUnit(textureUnit)
{
	uDiffuse = glGetUniformLocation(program, "material.diffuse");
	uSpecular = glGetUniformLocation(program, "material.specular");
	this->path = path;
	create(path, textureUnit);
}


Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::load(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	data=stbi_load(path, &width, &height, &channels,0);
	if (!data)
	{
		std::cout << "ERROR::FAILED_TO_OPEN:\"" << path << "\"" << std::endl;
		return;
	}

}



void Texture::create(const char* path,uint32_t textureUnit)
{
	load(path);
	uint32_t glformat = (channels == 4) ? GL_RGBA : GL_RGB;

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, glformat, width, height, 0, glformat,GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	
}

void Texture::Activate()
{
	//Setting uniform Sampler2d
	uint32_t CurrTexture;
	if ((GL_TEXTURE0 + textureUnit) == GL_TEXTURE0)
	{
		CurrTexture = uDiffuse;
	}
	else if ((GL_TEXTURE0 + textureUnit) == GL_TEXTURE1)
	{
		CurrTexture = uSpecular;
	}
	else
	{
		std::cout << "ERROR::INVALID_TEXTURE_UNIT" << std::endl;
		return;
	}

	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glEnable(GL_TEXTURE_2D);
	glUniform1i(CurrTexture, textureUnit);

	glBindTexture(GL_TEXTURE_2D, texture);
	
}
