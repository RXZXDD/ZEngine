#include "../public/BaseLogger.h"
#include "Logger/public/LoggerMisc.h"
#include "Logger/public/LoggerSuppressor.h"

#include <chrono>
#include <time.h>
#include <sstream>
#include <iostream>

namespace ZEngine {
	ZBaseLogger::ZBaseLogger(std::string InName) : Name(InName)
	{
		std::cout << Name.c_str() << std::endl;
		ZLoggerSuppressor::Get()->Associate(this);
	}
	ZLogRecord ZBaseLogger::Serialize(const LogLevel LogLevel, const std::string Msg)
	{


		const std::string_view LevelStr = LogLevelToString(LogLevel);
		std::stringstream Line;

		//add time
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);

		//TODO check char and wchar_t problem
		char str[26];
		ctime_s(str, sizeof str, &now_c);

		Line << "[" << str;
		Line.seekp(-1, std::ios_base::end);
		Line << "]";

		//add logger name
		Line << "[" << Name << "]";


		//add level
		Line << "[" << LevelStr.data() << "]" << ": "<< Msg << "\n";

		ZLogRecord Record{};
		Record.level = LogLevel;
		Record.loggerClsName = Name;
		Record.msg = Line.str();

		return Record;
	}
}