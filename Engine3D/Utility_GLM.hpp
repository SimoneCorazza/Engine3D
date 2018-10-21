#pragma once
/*
File containing utility methods, to expand GLM
*/

#include <glm\glm.hpp>


// Returns the array that encloses the information of the following vectors
// Example: to represent a model in 3D space
// @param[in] Location - Location vector
// @param[in] Scale - Scale vector
// @param[in] Rotation - Rotation vector (indicative of the individual axes)
const glm::mat4& Utility_GLM_MatrixFromVectors(const glm::vec3& Location, 
	const glm::vec3& Scale, const glm::vec3& Rotation);