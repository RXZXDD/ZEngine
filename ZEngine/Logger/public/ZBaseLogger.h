#pragma once

#include "Core/Core.h"
#include "LoggerMisc.h"

#include <chrono>
#include <time.h>
#include <sstream>
#include <iostream>

class ZBaseLogger
{
	std::string Name;

public:
	virtual std::string Serialize(const LogLevel LogLevel, const std::string Msg) {
		
		const std::string_view LevelStr = LogLevelToString(LogLevel);
		std::stringstream Line;

		//add time
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);

		char str[26];
		ctime_s(str, sizeof str, &now_c);

		Line << "[" << str;
		Line.seekp(-1, std::ios_base::end);
		Line << "]";
		
		//add logger name
		Line << "[" << Name << "]";
			
			
		//add level
		Line <<"[" << LevelStr.data() << "]" << ": " << Msg;
		

		return Line.str();
	}

	std::string_view GetName() const { return Name; }
};