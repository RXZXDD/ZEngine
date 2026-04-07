#pragma once
#include <cstdint>
#include <string_view>
#include <string>
#include <memory>
#include <iostream>


namespace ZEngine {

	class ZBaseLogger;

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

	std::string_view LogLevelToString(const LogLevel& l);

	struct ZLogParam
	{
		ZLogParam() = default;
		ZLogParam(LogLevel inLevel, ZBaseLogger* inCls, std::string inMsg) :level(inLevel), loggerCls(inCls), msg(inMsg) { };
		LogLevel level;
		ZBaseLogger* loggerCls;
		std::string msg;
		~ZLogParam() {
		//	std::cout << "releasing log" << std::endl;
		};
	};
}
