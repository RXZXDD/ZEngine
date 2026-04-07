#pragma once

#include "Core/Core.h"
#include "Core/Helper/public/ClassHelper.h"
//#include "LoggerMisc.h"

#include <chrono>
#include <time.h>
#include <sstream>
#include <iostream>

namespace ZEngine {

	struct ZLogRecord;
	enum class LogLevel : uint8_t;

	class ZBaseLogger
	{
		ZBaseLogger() = delete;
		CTR_CP_RM(ZBaseLogger)

	protected:
		std::string Name;

	public:
		ZBaseLogger(std::string InName);
		
		ZLogRecord Serialize(const LogLevel LogLevel, const std::string Msg);



		std::string_view GetName() const { return Name; }
	};



}