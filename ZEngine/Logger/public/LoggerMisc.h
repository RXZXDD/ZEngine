#pragma once
#include <cstdint>
#include <string_view>
#include <string>
#include <memory>

class ILogger;

//TODO turn into compile-time string
enum class LogLevel :uint8_t
{
	Display,
	Warning,
	Error,
	Fatal
};

namespace LogLevelString {
	static const std::string Display = "Display";
	static const std::string Warning = "Warning";
	static const std::string Error = "Error";
	static const std::string Fatal = "Fatal";
	static const std::string Unknown = "Unknown";
}

std::string_view LogLevelToString(const LogLevel& l) {
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
};

struct ZLogParam
{
	LogLevel level;
	std::shared_ptr<ILogger> loggerCls;
	std::string msg;
};