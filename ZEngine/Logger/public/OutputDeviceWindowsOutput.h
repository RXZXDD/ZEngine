#pragma once

#include "Core/Core.h"

#include "OutputDevice.h"

namespace ZEngine {
	class ZOutputDeviceWindowsOutput : public ZOutputDevice
	{

	public:

		void Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level) override;

	};
}