#pragma once
#include "fmt/core.h"
//#include "GlobalCore.h"
#include "Logger/public/BaseLogger.h"
#include "Logger/public/LoggerMisc.h"


//class ZEngine::ZBaseLogger;
//日志相关的宏

//ZLOG(Default, Display, TEXT("输出"))
#define ZLOG(LogCls, LogVobosity, Msg,...) \
{ \
        std::string InMsg = fmt::format(Msg,##__VA_ARGS__); \
        GLog->Log( ##LogCls.Serialize(ZEngine::LogLevel::LogVobosity, InMsg)); \
}

#define ZTEXT(X) u8##X

#define DECLARE_LOGGER_EXTERN(LogName) \
extern struct Z##LogName##Logger :public ZEngine::ZBaseLogger{\
    Z##LogName##Logger() :ZBaseLogger(#LogName){}\
} LogName;
 

#define DEFINE_LOGGER(LogName) \
struct Z##LogName##Logger LogName;