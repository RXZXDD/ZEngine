#pragma once
//显示在编辑器窗口的日志输出设备

#include "imgui.h"
#include "Misc/cpp/imgui_stdlib.h"

#include "Core/Core.h"
#include "Logger/public/OutputDevice.h"

namespace ZEngine
{
	class ZOutputDeviceTab : public ZOutputDevice
	{
		ZRingBuffer<std::unique_ptr<ZLogParam>> LogParams{ 50 };

		//ZDelegate OnNewLog;
		public:
		ZOutputDeviceTab();
		~ZOutputDeviceTab();
		virtual void Log(std::string Line, const ZBaseLogger* logger, const LogLevel level) override;


		typedef bool  (*InFn)(const char*, std::string*, const ImVec2&, ImGuiInputTextFlags , ImGuiInputTextCallback , void*);
		//显示日志到Tab窗口 TODO::分离ImgUI的包含，每帧都在循环读，尝试只在dirty时才重新读
		void DisplayLogToTab(InFn, const ImVec2& InVec, ImGuiInputTextFlags Flags);
	};
}