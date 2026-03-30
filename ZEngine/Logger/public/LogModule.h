#pragma once
#include "Core/Core.h"
#include "OutputDevice.h"
#include "OutputDeviceRedirector.h"
#include "LoggerSuppressor.h"

namespace ZEngine
{

	class LogModule
	{
		//Log suppressor
		std::unique_ptr<ZLoggerSuppressor> GLogSuppressor;

		//Log dispatcher
		std::unique_ptr<ZOutputDeviceRedirector> GLogDispatcher;

	public:
		LogModule();
		~LogModule();

		ZLoggerSuppressor* GetLogSuppressor() const { return GLogSuppressor.get(); }

		//return log dispatcher
		ZOutputDeviceRedirector* GetLogDispatcher() const { return GLogDispatcher.get(); }

	};

}