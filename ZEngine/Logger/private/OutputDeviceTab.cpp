#include "Logger/public/OutputDeviceTab.h"

ZEngine::ZOutputDeviceTab::ZOutputDeviceTab()
{
}

ZEngine::ZOutputDeviceTab::~ZOutputDeviceTab()
{
}

void ZEngine::ZOutputDeviceTab::Log(std::string Line, const ZBaseLogger* logger, const LogLevel level)
{
	//ZLogParam NewLog{};
	//NewLog.level = level;
	//NewLog.loggerCls = const_cast<ZBaseLogger*>(logger);
	//NewLog.msg = Line;

	LogParams.Push(std::move(ZLogParam{ level,const_cast<ZBaseLogger*>(logger),Line }));
	
	//OnNewLog->Broadcast();
}

void ZEngine::ZOutputDeviceTab::DisplayLogToTab(InFn InFnc, const ImVec2& InVec, ImGuiInputTextFlags Flags)
{
	std::string output;
	int cnt = 0;
	for (size_t i = LogParams.GetHeadIdx(); cnt < LogParams.GetSize();++cnt, i= LogParams.GetNextIdx(i))
	{
		//auto LogParam = *(LogParams[i]);
		output += (LogParams[i]).msg;

	}
	(*InFnc)("##", &output, InVec, Flags, nullptr, nullptr);
}

void ZEngine::ZOutputDeviceTab::Clear()
{
	LogParams.Reset();
}