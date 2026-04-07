#pragma once

#include "Core.h"
//#include "BaseLogger.h"

namespace ZEngine {

	class ZBaseLogger;
	enum class LogLevel : uint8_t;

	class ZOutputDevice {

	public:
		ZOutputDevice();
		virtual ~ZOutputDevice();

		virtual void Log(std::string Line)=0;

	};

}
