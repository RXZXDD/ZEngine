#include "../public/LoggerSuppressor.h"
#include "Logger/public/LoggerMacro.h"

DEFINE_LOGGER(Default)

namespace ZEngine
{

	ZLoggerSuppressor::ZLoggerSuppressor()
	{
		/*TempMemoLoggers.reserve(4);

		std::unique_ptr<ZBaseLogger> DefaultLogger = std::make_unique<ZBaseLogger>();
		TempMemoLoggers.push_back(std::move(DefaultLogger));

		AddLogger(TempMemoLoggers.back().get());*/

		//for (auto logger : PenddingLoggers) {
		//	if(logger)
		//		AddLogger(logger);
		//}
		//bIsInited = true;
	}

	ZLoggerSuppressor::~ZLoggerSuppressor()
	{
	}

	void ZLoggerSuppressor::Associate(ZBaseLogger* logger) {
		if (!bIsInited) {
			PenddingLoggers.push_back(logger);
			return;
		}
		else {
			AddLogger(logger);
		}
	}

	void ZLoggerSuppressor::ApplyConfig()
	{
		//TODO apply config
		bIsInited = true;

		for (auto logger : PenddingLoggers) {
			if (logger)
				AddLogger(logger);
		}

		PenddingLoggers.clear();
	}

	bool ZLoggerSuppressor::AddLogger(ZBaseLogger* logger)
	{

		if (logger) {
			if (Loggers.find(logger->GetName()) == Loggers.cend()) {
				Loggers[logger->GetName()] = logger;
				return true;
			}

		}
		return false;
	}

	//TODO: remove logger
	bool ZLoggerSuppressor::RemoveLogger(ZBaseLogger* logger)
	{
		return false;
	}

	std::optional<ZBaseLogger> ZLoggerSuppressor::GetLogger(std::string_view LoggerName) const
	{
		if (!bIsInited) {
			return std::optional<ZBaseLogger>();
		}
		auto retIt = Loggers.find(LoggerName);
		if (retIt != Loggers.cend()) {
			return std::optional<ZBaseLogger>(*(retIt->second));
		}
	
		return std::optional<ZBaseLogger>(std::nullopt);
	}

}