#include "../public/OutputDeviceWindowsOutput.h"
#include "Core/Helper/public/StringHelper.h"

#include <Windows.h>


void ZEngine::ZOutputDeviceWindowsOutput::Log(std::string Line, const ZBaseLogger* logger, const LogLevel level)
{
	std::wstring WLine;
	ZEngine::StringHelper::StringToWString(Line, WLine);
	OutputDebugString(WLine.c_str());
}
