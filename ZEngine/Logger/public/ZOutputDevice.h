#pragma once

#include "Core.h"


namespace ZEngine {
	class ZOutputDevice {

	protected:



	public:
		ZOutputDevice();
		~ZOutputDevice();

		virtual void Log(std::wstring Line) { };

		bool operator==(const ZOutputDevice& rhs) const {
			return this == &rhs;
		}
	};

}
