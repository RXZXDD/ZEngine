#include "../public/LoggerSuppressor.h"

namespace ZEngine
{

	ZLoggerSuppressor::ZLoggerSuppressor()
	{
		TempMemoLoggers.reserve(4);

		std::unique_ptr<ZBaseLogger> DefaultLogger = std::make_unique<ZBaseLogger>();
		TempMemoLoggers.push_back(std::move(DefaultLogger));

		AddLogger(TempMemoLoggers.back().get());
	}

	ZLoggerSuppressor::~ZLoggerSuppressor()
	{
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

	ZBaseLogger* ZLoggerSuppressor::GetLogger(std::wstring_view LoggerName) const
	{
		auto ret = Loggers.find(LoggerName);
		if (ret != Loggers.cend())
			return ret->second;
		return nullptr;
	}

}