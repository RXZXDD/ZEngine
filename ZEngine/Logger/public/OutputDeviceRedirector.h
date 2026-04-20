#pragma once

#include "Core/Containers/public/Array.h"
#include "Logger/public/OutputDevice.h"
#include "Core/Misc/LazySingleton.h"

namespace ZEngine
{
	//forward declare
	class ZOutputDeviceTab;
	struct ZLogRecord;

	class ZOutputDeviceRedirector : public ZOutputDevice
	{
		ZArray<ZOutputDevice*> Devices{};

		//TODO Temp memo for devices
		std::vector<std::unique_ptr<ZOutputDevice>> TempMemoDevices;
	public:
		ZOutputDeviceRedirector();

		bool AddOutputDevice(ZOutputDevice* device);

		bool RemoveOutputDevice(ZOutputDevice* device);

		virtual void Log(const ZLogRecord& Record) override;

		template<typename Ret>
		Ret* GetOutputDevice() const {
			for (auto& device : Devices) {
				if (auto ret = dynamic_cast<Ret*>(device)) {
					return ret;
				}
			}
			return nullptr;
		}

		ZOutputDeviceTab* GetOutputDeviceTab() const;

		static ZOutputDeviceRedirector* Get() {
			return TLazySingleton<ZOutputDeviceRedirector>::Get();
		}
	};
}