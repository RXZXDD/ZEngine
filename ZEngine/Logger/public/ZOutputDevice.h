#pragma once

#include "Core.h"
#include "ILogger.h"

struct ZLogParam;

class ZOutputDevice {

	protected:



	public:
		virtual void Log(std::string Line) {};

		bool operator==(const ZOutputDevice& rhs) const{
			return this == &rhs;
		}
};

