#pragma once
#include "Core/Core.h"
#include "Core/Misc/LazySingleton.h"


namespace ZEngine
{
	class ZBaseLogger;

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
		ZBaseLogger* GetLogger(std::string_view LoggerName) const;

		void Associate(ZBaseLogger* logger);

		void ApplyConfig();

		static ZLoggerSuppressor* Get() {
			return TLazySingleton<ZLoggerSuppressor>::Get();
		}
	};
}