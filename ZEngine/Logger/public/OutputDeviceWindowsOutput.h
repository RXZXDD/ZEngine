#pragma once

#include "Core/Core.h"

#include "OutputDevice.h"

namespace ZEngine {

	struct ZLogRecord;

	class ZOutputDeviceWindowsOutput : public ZOutputDevice
	{

	public:

		void Log(const ZLogRecord& Record) override;

	};
}