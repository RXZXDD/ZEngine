#pragma once
#include "Core/Core.h"
#include "OutputDevice.h"
#include "LoggerSuppressor.h"

namespace ZEngine
{
	class LogModule
	{
		//Log suppressor
		std::unique_ptr<ZLoggerSuppressor> GLogSuppressor;

		//Log dispatcher
		std::unique_ptr<ZOutputDevice> GLogDispatcher;

	public:
		LogModule();
		~LogModule();

		ZLoggerSuppressor* GetLogSuppressor() const { return GLogSuppressor.get(); }

		ZOutputDevice* GetLog() const { return GLogDispatcher.get(); }

	};

}