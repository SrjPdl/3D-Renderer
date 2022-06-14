#version 440 core

out vec4 colour;

in vec3 normal;
in vec2 texCoord;
in vec3 fragmentCoord;

uniform vec3 cameraPosition;

struct DirectionalLight
{
	vec3 colour;
	vec3 direction;

};

struct Material
{
	sampler2D diffuse;
	sampler2D specular;

	float specularReflectivity;
	float specularShine;
	float ambientReflectivity;
	float diffuseReflectivity;
};

uniform DirectionalLight directionalLight;
uniform Material material;

void main()
{	
	vec4 ambient = vec4(material.ambientReflectivity * directionalLight.colour, 1.f);

	/*Diffuse Lighting */
	//Angle between normal vector and light Direction vector
	float diffuseCosineAngle = max(dot(normalize(normal),normalize(directionalLight.direction)), 0.f);

	vec4 diffuse = vec4(
					 material.diffuseReflectivity
				   * directionalLight.colour
				   * diffuseCosineAngle,
				     1.f);

	
	/*Specular lighting*/
	vec4 specular = vec4(0.f, 0.f, 0.f, 1.f);
	if(bool(diffuseCosineAngle))
	{
		//unit vector from fragment to viewer
		vec3 V = normalize(fragmentCoord - cameraPosition);

		//unit reflection vector
		vec3 R = normalize(reflect(normalize(-directionalLight.direction), normalize(normal)));

		//Angle between V and R vector
		float specularCosineAngle = max(dot(V, R), 0.f);

		if(bool(specularCosineAngle))
		{
			specular = vec4(
						material.specularReflectivity
					  * pow(specularCosineAngle, material.specularShine)
					  * directionalLight.colour,
					    1.f);
		}
	}


	colour = texture(material.diffuse, texCoord) * (ambient + diffuse)
			+texture(material.specular,texCoord)*specular;
	
	if(colour.a < 0.5)
		{	discard;
		}
}