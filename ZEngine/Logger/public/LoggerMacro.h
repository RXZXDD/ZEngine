#pragma once

//日志相关的宏

//ZLOG(TempLog, Display, L"输出")
#define ZLOG(LogCls, LogVobosity, Msg) \
{\
auto logger = glogModule->GetLogSuppressor()->GetLogger(L#LogCls);\
if (logger)\
{\
    \
    std::wstring line = logger->Serialize(ZEngine::LogLevel::LogVobosity, L#Msg); \
    glogModule->GetLog()->Log(line, logger, ZEngine::LogLevel::LogVobosity);\
}\
}
