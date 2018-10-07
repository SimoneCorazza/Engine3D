#include <Windows.h>

/*
Variable used to tell the NVIDIA driver to use the dedicated card and not the one
integrated in the CPU (generally Intel). Useful when the PC is a laptop
http:// developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
*/


extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}