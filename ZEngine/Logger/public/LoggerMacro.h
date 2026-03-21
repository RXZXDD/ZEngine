#pragma once

//ZLOG(TempLog, Display, L"Êä³ö")
#define ZLOG(LogCls, LogVobosity, Msg) \
{\
auto logger = glogModule->GetLogSuppressor()->GetLogger(L#LogCls);\
if (logger)\
{\
    std::wstring line = logger->Serialize(ZEngine::LogLevel::LogVobosity, L#Msg); \
    glogModule->GetLog()->Log(line);\
}\
}
