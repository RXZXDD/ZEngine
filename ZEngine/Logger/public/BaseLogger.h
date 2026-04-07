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
	protected:
		std::string Name{ "Default" };

	public:
		ZBaseLogger() { std::cout << Name.c_str() << std::endl; };
		ZBaseLogger(std::string InName);
		
		std::string Serialize(const LogLevel LogLevel, const std::string Msg);



		std::string_view GetName() const { return Name; }
	};



}