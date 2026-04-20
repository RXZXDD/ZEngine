#pragma once

//#include "Core/Core.h"

#include "OutputDevice.h"

namespace ZEngine {

	struct ZLogRecord;

	class ZOutputDeviceConsole : public ZOutputDevice
	{

	public:
		ZOutputDeviceConsole();

		void Log(const ZLogRecord& Record) override;
		
	};
}