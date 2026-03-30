#pragma once

//日志相关的宏

//ZLOG(Default, Display, L"输出")
#define ZLOG(LogCls, LogVobosity, Msg) \
{\
auto logger = glogModule->GetLogSuppressor()->GetLogger(L#LogCls);\
if (logger)\
{\
    \
    const std::wstring InMsg = Msg;\
    std::wstring line = logger->Serialize(ZEngine::LogLevel::LogVobosity, InMsg); \
    glogModule->GetLogDispatcher()->Log(line, logger, ZEngine::LogLevel::LogVobosity);\
}\
}

