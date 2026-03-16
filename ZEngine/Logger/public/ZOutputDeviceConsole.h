#pragma once

#include "Core/Core.h"

#include "ZOutputDevice.h"

class ZOutputDeviceConsole : public ZOutputDevice
{

public:

	void Log(std::string Line) override;

};