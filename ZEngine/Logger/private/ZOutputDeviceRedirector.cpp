#pragma once
#include "../public/ZOutputDeviceRedirector.h"
#include "../public/ZOutputDeviceConsole.h"
#include "../public/ZOutputDeviceWindowsOutput.h"
#include "../public/ZOutputDeviceFile.h"


namespace ZEngine {
	ZOutputDeviceRedirector::ZOutputDeviceRedirector()
	{

		TempMemoDevices.reserve(4);

		auto consoleDevice = std::make_unique<ZOutputDeviceConsole>();
		TempMemoDevices.push_back(std::move(consoleDevice));
		AddOutputDevice(TempMemoDevices.back().get());

		auto DeBugoutputDevice = std::make_unique<ZOutputDeviceWindowsOutput>();
		TempMemoDevices.push_back(std::move(DeBugoutputDevice));
		AddOutputDevice(TempMemoDevices.back().get());

		auto FileoutputDevice = std::make_unique<ZOutputDeviceFile>();
		TempMemoDevices.push_back(std::move(FileoutputDevice));
		AddOutputDevice(TempMemoDevices.back().get());
	}

	bool ZOutputDeviceRedirector::AddOutputDevice(ZOutputDevice* device)
	{
		const int Num = Devices.size();
		if (Devices.AddUnique(device) == Num) {
			return true;
		}
		return false;
	}

	//TODO: remove device
	bool ZOutputDeviceRedirector::RemoveOutputDevice(ZOutputDevice* device)
	{

		auto fd = std::find(Devices.cbegin(), Devices.cend(), device);
		if (fd != Devices.cend()) {
			Devices.erase(fd);
			return true;
		}
		return false;
	}

	void ZOutputDeviceRedirector::Log(std::wstring Line)
	{
		for (auto& device : Devices) {
			device->Log(Line);
		}
	}

}