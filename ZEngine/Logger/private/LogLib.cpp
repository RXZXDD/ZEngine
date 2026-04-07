//#include <memory>
//#include "Core/Core.h"
//#include "Logger/public/LogModule.h"
//#include "Logger/public/BaseLogger.h"
//#include "../public/LogLib.h"
//
//extern std::unique_ptr<ZEngine::LogModule> glogModule;
//
//namespace ZEngine
//{
//		//bool LogLib::AddLogger(ZBaseLogger* logger)
//		//{
//		//	return false;
//		//	//TryGetGLog();
//		//	//return glogModule->GetLogSuppressor()->AddLogger(logger);
//		//}
//
//		//ZBaseLogger* LogLib::GetLogger(std::string_view clsName)
//		//{
//		//	return glogModule->GetLogSuppressor()->GetLogger(clsName);
//		//}
//
//		//void LogLib::Dispatch(std::string Line, const ZBaseLogger* logger, LogLevel level)
//		//{
//		//	glogModule->GetLogDispatcher()->Log(Line, logger, level);
//		//}
//
//		//void LogLib::TryGetGLog()
//		//{
//		//	if (!glogModule) {
//		//		glogModule = std::make_unique<ZEngine::LogModule>();
//		//	}
//		//	assert(glogModule);
//		//}
//}
