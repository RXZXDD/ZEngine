#include "../public/LoggerIniter.h"

LoggerInit::LoggerInit()
{
}

bool LoggerInit::AddLogger(ZBaseLogger* logger)
{
	if (logger ) {
		if (Loggers.find(logger->GetName()) == Loggers.cend()) {
			Loggers[logger->GetName()] = logger;
			return true;
		}

	}
	return false;
}

//TODO: remove logger
bool LoggerInit::RemoveLogger(ZBaseLogger* logger)
{
	return false;
}

ZBaseLogger* LoggerInit::GetLogger(std::string_view LoggerName) const
{
	auto ret = Loggers.find(LoggerName);
	if(ret != Loggers.cend())
		return ret->second;
	return nullptr;
}
