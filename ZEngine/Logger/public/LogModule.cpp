#include "../public/LogModule.h"
#include "../public/OutputDeviceRedirector.h"

#include <locale>
namespace ZEngine
{


	LogModule::LogModule()
	{
		//Initialize log suppressor
		GLogSuppressor = std::make_unique<ZLoggerSuppressor>();
		//Initialize log dispatcher
		GLogDispatcher = std::make_unique<ZOutputDeviceRedirector>();

		//中文本地化设置
		std::wcout.imbue(std::locale("chs"));
	}

	LogModule::~LogModule()
	{
		if(GLogSuppressor != nullptr) {
			GLogSuppressor.reset();
		}

		if(GLogDispatcher != nullptr) {
			GLogDispatcher.reset();
		}
	}
}