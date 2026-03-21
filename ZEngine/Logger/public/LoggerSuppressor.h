#pragma once
#include "Core/Core.h"
#include "ZBaseLogger.h"

namespace ZEngine
{
	class ZLoggerSuppressor
	{
		std::unordered_map<std::wstring_view, ZBaseLogger*> Loggers{};

		// temp memo for BaseLogger

		std::vector<std::unique_ptr<ZBaseLogger>> TempMemoLoggers;
	public:

		ZLoggerSuppressor();
		~ZLoggerSuppressor();
		bool AddLogger(ZBaseLogger* logger);
		bool RemoveLogger(ZBaseLogger* logger);
		ZBaseLogger* GetLogger(std::wstring_view LoggerName) const;
	};
}