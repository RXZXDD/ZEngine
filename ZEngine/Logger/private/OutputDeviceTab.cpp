#include "Logger/public/OutputDevice.h"
#include "Logger/public/OutputDeviceTab.h"
#include "Logger/public/LoggerMisc.h"




ZEngine::ZOutputDeviceTab::~ZOutputDeviceTab()
{
}

void ZEngine::ZOutputDeviceTab::Log(const ZLogRecord& Record)
{

	LogParams.Push(std::move(ZLogRecord{Record}));
	OnNewLog.ExecuteIfSafe(LogParams.Tail());
}


void ZEngine::ZOutputDeviceTab::Clear()
{
	LogParams.Reset();
}