#pragma once

#include "Core.h"
#include "BaseLogger.h"

namespace ZEngine {
	class ZOutputDevice {

	protected:



	public:
		ZOutputDevice();
		virtual ~ZOutputDevice();

		virtual void Log(std::wstring Line, const ZBaseLogger* LogCls, const LogLevel level)=0;

	};

}
