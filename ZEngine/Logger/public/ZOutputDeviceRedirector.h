#pragma once

#include "Core/Core.h"

#include "ZOutputDevice.h"

class ZOutputDeviceRedirector : public ZOutputDevice
{
	ZArray<ZOutputDevice*> Devices{};
	public:
		ZOutputDeviceRedirector();

		bool AddOutputDevice(ZOutputDevice* device);
		
		bool RemoveOutputDevice(ZOutputDevice* device);

		void Log(std::string Line) override;
		
};