#include "../public/LogModule.h"
#include "../public/OutputDeviceRedirector.h"

namespace ZEngine
{


	LogModule::LogModule()
	{
		//Initialize log suppressor
		GLogSuppressor = std::make_unique<ZLoggerSuppressor>();
		//Initialize log dispatcher
		GLogDispatcher = std::make_unique<ZOutputDeviceRedirector>();

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