#include "Logger/public/OutputDeviceTab.h"

ZEngine::ZOutputDeviceTab::ZOutputDeviceTab()
{
}

ZEngine::ZOutputDeviceTab::~ZOutputDeviceTab()
{
}

void ZEngine::ZOutputDeviceTab::Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level)
{
	auto NewLog = std::make_unique<ZLogParam>();
	NewLog->level = level;
	NewLog->loggerCls = const_cast<ZBaseLogger*>(logger);
	NewLog->msg = Line;

	LogParams.Push(std::move(NewLog));
	
	//OnNewLog->Broadcast();
}
