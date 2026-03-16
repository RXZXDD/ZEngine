#pragma once
#include "Core.h"
#include "../public/ILogger.h"
#include <chrono>

std::string GetCurrentTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	return buf;
}


class CoreLogger : public ILogger
{
	public:
	/*virtual void Print(const LogClass level, const std::string message) override
	{
		std::string logMessage = "[" + GetCurrentTime() + "][" + GetLogClassString(level) + "]: " + message;
		WriteToLogFile(logMessage);

	}*/
};