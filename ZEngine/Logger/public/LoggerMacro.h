#pragma once
#include "fmt/core.h"

//日志相关的宏

//ZLOG(Default, Display, TEXT("输出"))
#define ZLOG(LogCls, LogVobosity, Msg,...) \
{\
auto logger = glogModule->GetLogSuppressor()->GetLogger(#LogCls);\
if (logger)\
{\
    \
    std::string InMsg = fmt::format(Msg, __VA_ARGS__);\
    std::string line = logger->Serialize(ZEngine::LogLevel::LogVobosity, InMsg); \
    glogModule->GetLogDispatcher()->Log(line, logger, ZEngine::LogLevel::LogVobosity);\
}\
}

#define ZTEXT(X) u8##X