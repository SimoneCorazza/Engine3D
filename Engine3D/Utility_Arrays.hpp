#pragma once

/*
Set of methods designed to provide useful methods for manipulating arrays
*/



// Copies a portion of the array indicated by the indicated size
// @param [in] OffsetX - X coordinate of the sub-matrix start point in number of elements
// @param [in] OffsetY - Y coordinate of the sub-matrix start point in number of elements
// @param [in] Width - Dimension on the X axis of the sub-matrix in number of elements
// @param [in] Height - Size on the Y axis of the sub-matrix in number of elements
// @param [in] SizeElement - Size of an element in bytes> 0
// @param [in] Matrix - Matrix from which to derive the sub-matrix
// @param [in] MatrixWid - Number of columns in the array (in number of elements)
// @param [in] MatrixHei - Number of rows of the matrix (in number of elements)
void* Utility_Arrays_SubMatrix(const size_t& OffsetX, const size_t& OffsetY, const size_t& Width, const size_t& Height, const size_t& SizeElement, 
	void* Matrix, const size_t& MatrixWid, const size_t& MatrixHei);