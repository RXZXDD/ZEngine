#pragma once

#define ZLOG(LogLevel,Logger, Msg) {/
	auto logger = LoggerInit->GetLogger(Logger); \
	if (logger) {
		\
			std::string line = logger->Serialize(LogLevel, Msg); \
			GLOG->Log(line);
		}\
}
