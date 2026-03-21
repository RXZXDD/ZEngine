#include "Logger/public/LoggerMisc.h"

std::string_view ZEngine::LogLevelToString(const LogLevel& l)
{
	switch (l)
	{
	case LogLevel::Display:
		return LogLevelString::Display;
	case LogLevel::Warning:
		return LogLevelString::Warning;
	case LogLevel::Error:
		return LogLevelString::Error;
	case LogLevel::Fatal:
		return LogLevelString::Fatal;
	default:
		return LogLevelString::Unknown;
	}

}
