#include "Material.h"

Material::Material(uint32_t program, float ambientReflectivity, float diffuseReflectivity, float specularReflectivity, float specularShine)
	:program(program),
	 ambientReflectivity(ambientReflectivity),
	 diffuseReflectivity(diffuseReflectivity),
	 specularReflectivity(specularReflectivity),
	 specularShine(specularShine)
{
	uSpecularReflectivity = glGetUniformLocation(program, "material.specularReflectivity");
	uSpecularShine = glGetUniformLocation(program, "material.specularShine");
	uAmbientReflectivity = glGetUniformLocation(program, "material.ambientReflectivity");
	uDiffuseReflectivity = glGetUniformLocation(program, "material.diffuseReflectivity");
}

void Material::update()
{
	//this->specularReflectivity = specularReflectivity;
	//this->specularShine = specularShine;
	glUniform1f(uSpecularReflectivity, this->specularReflectivity);
	glUniform1f(uSpecularShine, this->specularShine);
	glUniform1f(uAmbientReflectivity, this->ambientReflectivity);
	glUniform1f(uDiffuseReflectivity, this->diffuseReflectivity);
}
