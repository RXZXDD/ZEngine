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
		std::wstring Name{ L"Default" };

	public:
		ZBaseLogger() {};
		ZBaseLogger(std::wstring InName) : Name(InName) {}
		
		std::wstring Serialize(const LogLevel LogLevel, const std::wstring Msg);



		std::wstring_view GetName() const { return Name; }
	};


}