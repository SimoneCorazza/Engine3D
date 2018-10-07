#pragma once

// Indicates how the cursor will be treated by the application
enum IE_CursorMode
{
	IE_CursorMode_Normal, // Cursor displayed as per operating system
	IE_CursorMode_Hide, // Hidden cursor (not displayed)
	IE_CursorMode_Disabled, // Cursor disabled (suitable for a 3D camera)
};