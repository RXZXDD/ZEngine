#include "../public/ZOutputDeviceConsole.h"
#include "../public/LoggerMisc.h"
#include <chrono>
#include <time.h>
#include <sstream>
#include <iostream>

#define __STDC_WANT_LIB_EXT1__ 1

void ZOutputDeviceConsole::Log(std::string Line)
{
	//const std::string_view LevelStr = LogLevelToString(param.level);
	//std::stringstream Line;

	////add time
	//auto now = std::chrono::system_clock::now();
	//std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	//char str[26];
	//ctime_s(str, sizeof str, &now_c);

	//Line << "[" << str;
	//Line.seekp(-1, std::ios_base::end);

	//Line << "]" << "[" << LevelStr.data() << "]" << ": " << param.msg;
	////add level

	////add logger class name
	////TODO ->GetClassName()impl in compile-time
	////Line << "[" + param.loggerCls->GetClassName()<<"]";

	////add message

	std::cout << Line.c_str() << std::endl;

}
