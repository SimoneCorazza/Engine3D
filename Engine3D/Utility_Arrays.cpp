#include "Utility_Arrays.hpp"

#include "DEBUG.hpp"

void* Utility_Arrays_SubMatrix(const size_t& OffsetX, const size_t& OffsetY, const size_t& Width, const size_t& Height, const size_t& SizeElement,
	void* Matrix, const size_t& MatrixWid, const size_t& MatrixHei)
{
	ASSERT(Matrix != nullptr || Width * Height == 0, "Utility_Arrays_SubMatrix(): Matrix is null and size > 0");

	char* mat = (char*)Matrix;

	// Calculating the size of a row in bytes
	size_t rowSize = SizeElement * MatrixWid;
	
	// Allocate space for the new array
	char* copy = new char[Width * Height * SizeElement];

	int d = 0;
	for (int y = OffsetY; y < OffsetY + Height; y++)
		for (int x = OffsetX; x < OffsetX + Width; x++)
		{
			for (int i = 0; i < SizeElement; i++, d++)
				copy[d] = mat[y * rowSize + x * SizeElement + i];
		}

	return copy;
}