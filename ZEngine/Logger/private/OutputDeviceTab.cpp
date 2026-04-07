#include "imgui.h"
#include "Misc/cpp/imgui_stdlib.h"

#include "Logger/public/OutputDevice.h"
#include "Logger/public/OutputDeviceTab.h"
#include "Logger/public/LoggerMisc.h"

ZEngine::ZOutputDeviceTab::ZOutputDeviceTab()
{
}

ZEngine::ZOutputDeviceTab::~ZOutputDeviceTab()
{
}

void ZEngine::ZOutputDeviceTab::Log(const ZLogRecord& Record)
{
	//ZLogRecord copyRecord = Record;

	LogParams.Push(std::move(ZLogRecord{Record}));
	IsDirty = true;
	//OnNewLog->Broadcast();
}

void ZEngine::ZOutputDeviceTab::DisplayLogToTab(InFn InFnc, const ImVec2& InVec, ImGuiInputTextFlags Flags)
{
	
	if (IsDirty) {
		int cnt = 0;
		OutputCache.clear();
		for (size_t i = LogParams.GetHeadIdx(); cnt < LogParams.GetSize(); ++cnt, i = LogParams.GetNextIdx(i))
		{
			OutputCache += (LogParams[i]).msg;
		}
		IsDirty = false;
	}
	(*InFnc)("##", &OutputCache, InVec, Flags, nullptr, nullptr);
}

void ZEngine::ZOutputDeviceTab::Clear()
{
	LogParams.Reset();
	IsDirty = true;
}