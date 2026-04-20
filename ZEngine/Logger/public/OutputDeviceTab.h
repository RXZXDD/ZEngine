#pragma once
//显示在编辑器窗口的日志输出设备


//#include "Core/Core.h"

#include <string>

#include "Logger/public/OutputDevice.h"

#include "Core/Containers/public/RingBuffer.h"
#include "Core/Delegate/DelegateMacro.h"

namespace ZEngine
{
	//forward declare
	struct ZLogRecord;
	class ZBaseLogger;


	DECLEAR_DELEGATE_ONE_PARAM(FNewLog, const ZLogRecord&)

	class ZOutputDeviceTab : public ZOutputDevice
	{
		ZRingBuffer<ZLogRecord> LogParams{ 50 };

		public:
			ZOutputDeviceTab() = default;
			~ZOutputDeviceTab();
			virtual void Log(const ZLogRecord& Record) override;

			void Clear();

		public:
			FNewLog OnNewLog;
	};
}