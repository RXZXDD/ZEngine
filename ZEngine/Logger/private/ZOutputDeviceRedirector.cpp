#pragma once
#include "../public/ZOutputDeviceRedirector.h"
#include "../public/ZOutputDeviceConsole.h"

ZOutputDeviceRedirector::ZOutputDeviceRedirector()
{
	//TODO …Í«Îƒ⁄¥Ê¥Ê¥¢
	auto consoleDevice = std::make_unique<ZOutputDeviceConsole>();
	AddOutputDevice(consoleDevice.get());
}

bool ZOutputDeviceRedirector::AddOutputDevice(ZOutputDevice* device)
{
	const int Num = Devices.size();
	if (Devices.AddUnique(device) == Num) {
		return true;
	}
	return false;
}

bool ZOutputDeviceRedirector::RemoveOutputDevice(ZOutputDevice* device)
{

	auto fd = std::find(Devices.cbegin(), Devices.cend(), device);
	if (fd != Devices.cend()) {
		Devices.erase(fd);
		return true;
	}
	return false;
}

void ZOutputDeviceRedirector::Log(std::string Line)
{
	for (auto& device : Devices) {
		device->Log(Line);
	}
}
