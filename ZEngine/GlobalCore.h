#include "Core/Core.h"
#include "Logger/public/ZOutputDevice.h"

//Log dispatcher
std::unique_ptr<ZOutputDevice> GLog;

ZOutputDevice* GetLogSigleton()
{
	if (GLog == nullptr)
		GLog = std::make_unique<ZOutputDeviceRedirector>();
	return GLog.get();
}

