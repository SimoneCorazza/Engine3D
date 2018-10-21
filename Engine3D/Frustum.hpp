#pragma once

#include <glm\glm.hpp>
#include "Plane.hpp"

class Box;




// Class that allows to determine if a point is inside the visible space of the camera
class Frustum
{
	// Arrays of the planes that make up the frustum culling are in order:
	// Right, Left, Bottom, Top, Far, Near
	Plane frustum[6];

public:
	Frustum();
	~Frustum();


public:

	// Set the Fstrum plans given the camera
	// @param[in] m - Matrix of the camera
	void setPlanes(const glm::mat4& m);

	
	// Check if the indicated point is within the visual cone
	// @param[in] V - Point to be tested
	// @return True if the point is in the visual field
	bool TestView(const glm::vec3& V);

	// Check if the indicated box is within the visual cone
	// @param[in] B - Box to be tested
	// @return True if the box is in the visual field
	bool TestView(const Box* B);

	// Check if the sphere is visible in the visual cone
	// @param[in] O - Origin of the sphere
	// @param[in] Radius - Radius of the sphere
	bool TestView(const glm::vec3& O, float Radius);

private:

	// Indicates which side of the plane is the vertex
	// @param[in] P - Plan
	// @param[in] V - Summit
	// @return True the vertex is in the positive portion of the plane [0, + inf [
	inline bool TestViewPlane(const Plane& P, const glm::vec3& V);
};

