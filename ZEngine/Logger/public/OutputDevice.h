#pragma once

//#include "Core.h"
////#include "BaseLogger.h"

namespace ZEngine {

	class ZBaseLogger;
	struct ZLogRecord;

	class ZOutputDevice {

	public:
		ZOutputDevice();
		virtual ~ZOutputDevice();

		virtual void Log(const ZLogRecord& Record)=0;

	};

}
