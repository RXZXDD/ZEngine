#include "../public/ZOutputDeviceWindowsOutput.h"
#include "Core/Helper/public/StringHelper.h"

#include <Windows.h>


void ZEngine::ZOutputDeviceWindowsOutput::Log(std::wstring Line)
{
	OutputDebugString(Line.c_str());
}
