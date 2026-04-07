#include "Logger/public/OutputDevice.h"
#include "GlobalCore.h"

namespace ZEngine
{
	ZOutputDevice::ZOutputDevice()
	{
	}

	ZOutputDevice::~ZOutputDevice()
	{
		if (GLog) {
			GLog->RemoveOutputDevice(this);
		}

	}

}
