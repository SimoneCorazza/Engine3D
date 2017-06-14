#include <Windows.h>

/*
Variabile utilizzata per indicare al driver NVIDIA di utilizzare la scheda dedicata e non quella
integrata nella CPU (generalmente Intel). Utile quando il PC è un portatile
http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
*/


extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}