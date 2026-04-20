#pragma once
#include "../public/OutputDeviceRedirector.h"
#include "../public/OutputDeviceConsole.h"
#include "../public/OutputDeviceWindowsOutput.h"
#include "../public/OutputDeviceFile.h"
#include "../public/OutputDeviceTab.h"


namespace ZEngine {
	ZOutputDeviceRedirector::ZOutputDeviceRedirector()
	{

		TempMemoDevices.reserve(4);

		TempMemoDevices.push_back(std::move(std::make_unique<ZOutputDeviceConsole>()));
		AddOutputDevice(TempMemoDevices.back().get());

		TempMemoDevices.push_back(std::move(std::make_unique<ZOutputDeviceWindowsOutput>()));
		AddOutputDevice(TempMemoDevices.back().get());

		TempMemoDevices.push_back(std::move(std::make_unique<ZOutputDeviceFile>()));
		AddOutputDevice(TempMemoDevices.back().get());

		TempMemoDevices.push_back(std::move(std::make_unique<ZOutputDeviceTab>()));
		AddOutputDevice(TempMemoDevices.back().get());
		
	}

	bool ZOutputDeviceRedirector::AddOutputDevice(ZOutputDevice* device)
	{
		const size_t Num = Devices.size();
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

	void ZEngine::ZOutputDeviceRedirector::Log(const ZLogRecord& Record)
	{
		//TODO: 暂未考虑读取config的情况，默认创建分发器自动创建输出设备
		for (auto device : Devices) {
			if(device)
				device->Log(Record);
		}
	}

	ZOutputDeviceTab* ZOutputDeviceRedirector::GetOutputDeviceTab() const
	{
		return GetOutputDevice<ZOutputDeviceTab>();
	}

}