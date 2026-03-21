#include "../public/ZBaseLogger.h"
#include "Logger/public/LoggerMisc.h"

namespace ZEngine {
	std::wstring ZBaseLogger::Serialize(const LogLevel LogLevel, const std::wstring Msg)
	{

		const std::string_view LevelStr = LogLevelToString(LogLevel);
		std::wstringstream Line;

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
		Line << "[" << LevelStr.data() << "]" << ": " << Msg;


		return Line.str();
	}
}