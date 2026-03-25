#pragma once
//显示在编辑器窗口的日志输出设备
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
		virtual void Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level) override;
	};
}