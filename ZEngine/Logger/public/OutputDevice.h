#pragma once

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
