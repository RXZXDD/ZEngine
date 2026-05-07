#include "../public/OutputDeviceWindowsOutput.h"
#include "Core/Helper/public/StringHelper.h"
#include "../public/LoggerMisc.h"

//#include <Windows.h>


void ZEngine::ZOutputDeviceWindowsOutput::Log(const ZLogRecord& Record)
{
	std::wstring WLine;
	ZEngine::StringHelper::StringToWString(Record.msg, WLine);
	OutputDebugString(WLine.c_str());
}
