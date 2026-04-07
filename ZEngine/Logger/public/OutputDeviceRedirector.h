#pragma once

#include "Core/Core.h"

#include "Logger/public/OutputDevice.h"
#include "Logger/public/OutputDeviceTab.h"

#include "Core/Misc/LazySingleton.h"

namespace ZEngine
{
	class ZOutputDevice;
	static_assert(sizeof(ZOutputDevice) > 0, "基类未定义！");
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

		ZOutputDeviceTab* GetOutputDeviceTab() const {
			return GetOutputDevice<ZOutputDeviceTab>();
		}

		static ZOutputDeviceRedirector* Get() {
			return TLazySingleton<ZOutputDeviceRedirector>::Get();
		}
	};
}