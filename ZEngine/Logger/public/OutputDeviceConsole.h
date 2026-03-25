#pragma once

#include "Core/Core.h"

#include "OutputDevice.h"

namespace ZEngine {
	class ZOutputDeviceConsole : public ZOutputDevice
	{

	public:

		void Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level) override;

	};
}