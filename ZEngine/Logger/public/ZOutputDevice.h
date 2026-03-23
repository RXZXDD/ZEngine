#pragma once

#include "Core.h"


namespace ZEngine {
	class ZOutputDevice {

	protected:



	public:
		ZOutputDevice();
		virtual ~ZOutputDevice();

		virtual void Log(std::wstring Line) { };

	};

}
