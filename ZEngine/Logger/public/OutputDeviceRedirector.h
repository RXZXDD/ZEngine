#pragma once

#include "Core/Core.h"

#include "Logger/public/OutputDevice.h"

namespace ZEngine
{
	class ZOutputDeviceRedirector : public ZOutputDevice
	{
		ZArray<ZOutputDevice*> Devices{};

		//TODO Temp memo for devices
		std::vector<std::unique_ptr<ZOutputDevice>> TempMemoDevices;
	public:
		ZOutputDeviceRedirector();

		bool AddOutputDevice(ZOutputDevice* device);

		bool RemoveOutputDevice(ZOutputDevice* device);

		virtual void Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level) override;

	};
}