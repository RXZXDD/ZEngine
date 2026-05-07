#pragma once

#include "OutputDevice.h"

namespace ZEngine {

	struct ZLogRecord;

	class ZOutputDeviceWindowsOutput : public ZOutputDevice
	{

	public:

		void Log(const ZLogRecord& Record) override;

	};
}