#include "Utility_GLM.h"

#include <glm\gtc\matrix_transform.hpp>


const glm::mat4& Utility_GLM_MatrixFromVectors(const glm::vec3& Location, 
	const glm::vec3& Scale, const glm::vec3& Rotation)
{
	glm::mat4 t = glm::translate(glm::mat4(1), Location);
	glm::mat4 s = glm::scale(t, Scale);
	glm::mat4 r_x = glm::rotate(glm::mat4(1), Rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 r_y = glm::rotate(glm::mat4(1), Rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 r_z = glm::rotate(glm::mat4(1), Rotation.z, glm::vec3(0, 0, 1));
	return s * r_x * r_y * r_z;
}