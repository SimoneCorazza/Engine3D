#include "Material.hpp"

#include "DEBUG.hpp"

Material::Material()
{
	shader = nullptr;
	texture = nullptr;
	DefaultLightSettings();
}


Material::Material(ModelShader* Shader, const Texture2D* Texture)
{
	ASSERT(Texture != nullptr, "Material::Material(): param Texture is null");

	shader = Shader;
	texture = Texture;
	DefaultLightSettings();
}

Material::~Material()
{
}





ModelShader * Material::getShader() const
{
	return shader;
}

const Texture2D * Material::getTexture() const
{
	return texture;
}

void Material::setAmbient(const glm::vec3 & V)
{
	ambient = V;
}

const glm::vec3 & Material::getAmbient() const
{
	return ambient;
}

void Material::setDiffuse(const glm::vec3 & V)
{
	diffuse = V;
}

const glm::vec3 & Material::getDiffuse() const
{
	return diffuse;
}

void Material::setSpecular(const glm::vec3 & V)
{
	specular = V;
}

const glm::vec3 & Material::getSpecular() const
{
	return specular;
}

void Material::setShininess(float S)
{
	shininess = S;
}

float Material::getShininess() const
{
	return shininess;
}

inline void Material::DefaultLightSettings()
{
	ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	diffuse = glm::vec3(1.0f, 0.8f, 1.0f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);
	shininess = 5.f;
}
