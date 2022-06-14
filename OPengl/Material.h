#pragma once
#include<gl/glew.h>
#include <iostream>
class Material
{
	private:
		float specularReflectivity;
		float specularShine;
		float ambientReflectivity;
		float diffuseReflectivity;

		uint32_t uAmbientReflectivity;
		uint32_t uDiffuseReflectivity;
		uint32_t program;
		uint32_t uSpecularReflectivity;
		uint32_t uSpecularShine;
		
	public:
		Material(uint32_t program, float ambientReflectivity = 0.2f, float diffuseReflectivity = 0.6f, float specularReflectivity=1.f, float specularShine = 32);
		void update();


};


