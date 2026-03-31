#include "Logger/public/OutputDeviceTab.h"

ZEngine::ZOutputDeviceTab::ZOutputDeviceTab()
{
}

ZEngine::ZOutputDeviceTab::~ZOutputDeviceTab()
{
}

void ZEngine::ZOutputDeviceTab::Log(std::string Line, const ZBaseLogger* logger, const LogLevel level)
{
	auto NewLog = std::make_unique<ZLogParam>();
	NewLog->level = level;
	NewLog->loggerCls = const_cast<ZBaseLogger*>(logger);
	NewLog->msg = Line;

	LogParams.Push(std::move(NewLog));
	
	//OnNewLog->Broadcast();
}

void ZEngine::ZOutputDeviceTab::DisplayLogToTab(InFn InFnc, const ImVec2& InVec, ImGuiInputTextFlags Flags)
{
	std::string output;

	for (auto i = LogParams.GetHead(); i < LogParams.GetTail();i= LogParams.GetNext(i))
	{
		auto LogParam = *(LogParams[i]);
		output += LogParam.msg;

	}
	(*InFnc)("##", &output, InVec, Flags, nullptr, nullptr);
}
