#include "../public/OutputDeviceWindowsOutput.h"
#include "Core/Helper/public/StringHelper.h"

#include <Windows.h>


void ZEngine::ZOutputDeviceWindowsOutput::Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level)
{
	OutputDebugString(Line.c_str());
}
