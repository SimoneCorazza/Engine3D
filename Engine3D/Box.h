#pragma once


#include <glm\glm.hpp>
#include <GL\glew.h>

// Class representing a box, 3D box
// 
/* Verteces scheme:
Axis:
^
Z|
|
O------>     (Y exits upword from the screen)
Y      X
Bottom part:				Top part:
V1--------V4					V5--------V8
|		  |						|		  |
|		  |						|		  |
V2--------V3					V6--------V7
*/
class Box
{
	// Vertexes of the Box
	public: glm::vec3 v1, v2, v3, v4, v5, v6, v7, v8;

	public:
		Box();

		// Create a box centered on the origin with these dimensions
		Box(float Width, float Height, float Depth);

		// Creates a box centered in the origin that respects the indicated limits, for each axis
		Box(float MaxX, float MinX, float MaxY, float MinY, float MaxZ, float MinZ);

		~Box();

	public:

		const glm::vec3& getV1() const;
		const glm::vec3& getV2() const;
		const glm::vec3& getV3() const;
		const glm::vec3& getV4() const;

		const glm::vec3& getV5() const;
		const glm::vec3& getV6() const;
		const glm::vec3& getV7() const;
		const glm::vec3& getV8() const;


		Box* Box::operator*(const glm::mat4& matrix) const
		{
			Box* b = new Box();
			// NOTE: in the multiplication the matrix goes to the left side, otherwise it has
			// the opposite effect (eg reverse rotation)
			b->v1 = glm::vec3(matrix * glm::vec4(this->v1, 1));
			b->v2 = glm::vec3(matrix * glm::vec4(this->v2, 1));
			b->v3 = glm::vec3(matrix * glm::vec4(this->v3, 1));
			b->v4 = glm::vec3(matrix * glm::vec4(this->v4, 1));
			b->v5 = glm::vec3(matrix * glm::vec4(this->v5, 1));
			b->v6 = glm::vec3(matrix * glm::vec4(this->v6, 1));
			b->v7 = glm::vec3(matrix * glm::vec4(this->v7, 1));
			b->v8 = glm::vec3(matrix * glm::vec4(this->v8, 1));

			return b;
		}
};

