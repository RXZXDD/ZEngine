#pragma once

#include "Core/Core.h"

#include "Logger/public/ZOutputDevice.h"

namespace ZEngine
{
	class ZOutputDeviceRedirector : public ZOutputDevice
	{
		ZArray<ZOutputDevice*> Devices{};

		//Temp memo for devices
		std::vector<std::unique_ptr<ZOutputDevice>> TempMemoDevices;
	public:
		ZOutputDeviceRedirector();

		bool AddOutputDevice(ZOutputDevice* device);

		bool RemoveOutputDevice(ZOutputDevice* device);

		virtual void Log(std::wstring Line) override;

	};
}