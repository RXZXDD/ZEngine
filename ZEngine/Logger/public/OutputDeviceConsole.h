#pragma once

#include "Core/Core.h"

#include "OutputDevice.h"

namespace ZEngine {
	class ZOutputDeviceConsole : public ZOutputDevice
	{

	public:
		ZOutputDeviceConsole();
		void Log(std::string Line, const ZBaseLogger* logger, const LogLevel level) override;

	};
}