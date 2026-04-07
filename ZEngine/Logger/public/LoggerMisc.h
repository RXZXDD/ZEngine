#pragma once
#include <cstdint>
#include <string_view>
#include <string>
#include <memory>
#include <iostream>


namespace ZEngine {

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

	struct ZLogRecord
	{
		ZLogRecord() = default;
		ZLogRecord(LogLevel inLevel, std::string_view inClsName, std::string inMsg) :level(inLevel), loggerClsName(inClsName), msg(inMsg) { };
		ZLogRecord(const ZLogRecord& other) {
			if (this != &other) {
				level = other.level;
				loggerClsName = other.loggerClsName;
				msg = other.msg;
				//std::cout << "copying log: " << loggerClsName << std::endl;
			}
		}

		LogLevel level = LogLevel::Display;
		std::string_view loggerClsName;
		std::string msg;
		~ZLogRecord() {
			//std::cout << "releasing log: " << loggerClsName << std::endl;
		};
	};
}
