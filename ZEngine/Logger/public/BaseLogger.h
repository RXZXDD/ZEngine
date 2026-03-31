#pragma once

#include "Core/Core.h"
#include "LoggerMisc.h"

#include <chrono>
#include <time.h>
#include <sstream>
#include <iostream>

namespace ZEngine {
	class ZBaseLogger
	{
		std::string Name{ "Default" };

	public:
		ZBaseLogger() {};
		ZBaseLogger(std::string InName) : Name(InName) {}
		
		std::string Serialize(const LogLevel LogLevel, const std::string Msg);



		std::string_view GetName() const { return Name; }
	};


}