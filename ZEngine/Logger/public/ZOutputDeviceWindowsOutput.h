#pragma once

#include "Core/Core.h"

#include "ZOutputDevice.h"

namespace ZEngine {
	class ZOutputDeviceWindowsOutput : public ZOutputDevice
	{

	public:

		void Log(std::wstring Line) override;

	};
}