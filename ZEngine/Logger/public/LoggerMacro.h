#pragma once
#include "fmt/core.h"
#include "Logger/public/BaseLogger.h"
#include "Logger/public/LoggerMisc.h"


//class ZEngine::ZBaseLogger;
//日志相关的宏

//ZLOG(Default, Display, TEXT("输出"))
#define ZLOG(LogCls, LogVobosity, Msg,...) \
{ \
        std::string InMsg = fmt::format(Msg,##__VA_ARGS__); \
        GLog->Log( Log##LogCls.Serialize(ZEngine::LogLevel::LogVobosity, InMsg)); \
}

#define ZTEXT(X) u8##X

#define DECLARE_LOGGER_EXTERN(Name) \
extern struct Z##Name##Logger :public ZEngine::ZBaseLogger{\
    Z##Name##Logger() :ZBaseLogger(#Name){}\
} Log##Name;
 

#define DEFINE_LOGGER(Name) \
struct Z##Name##Logger Log##Name;