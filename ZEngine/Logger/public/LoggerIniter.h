#pragma once
#include "Core/Core.h"
#include "ZBaseLogger.h"

class LoggerInit
{
	std::unordered_map<std::string_view, ZBaseLogger*> Loggers{};

public: 
	LoggerInit();
	bool AddLogger(ZBaseLogger* logger);
	bool RemoveLogger(ZBaseLogger* logger);
	ZBaseLogger* GetLogger(std::string_view LoggerName) const;
};