#pragma once
#include "Core/Core.h"
#include "BaseLogger.h"
#include "Core/Misc/LazySingleton.h"
#include "Logger/public/LoggerMacro.h"
#include <optional>

DECLARE_LOGGER_EXTERN(Default)

namespace ZEngine
{

	class ZLoggerSuppressor
	{
		std::unordered_map<std::string_view, ZBaseLogger*> Loggers{};

		std::vector<ZBaseLogger*> PenddingLoggers;

		bool bIsInited = false;
	public:

		ZLoggerSuppressor();
		~ZLoggerSuppressor();
		bool AddLogger(ZBaseLogger* logger);
		bool RemoveLogger(ZBaseLogger* logger);
		std::optional<ZBaseLogger> GetLogger(std::string_view LoggerName) const;

		void Associate(ZBaseLogger* logger);

		void ApplyConfig();

		static ZLoggerSuppressor* Get() {
			return TLazySingleton<ZLoggerSuppressor>::Get();
		}
	};
}