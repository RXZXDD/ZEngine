#pragma once

#include <string>

#include "../public/Tab.h"

namespace ZEngine {

	//forward declare
	class ZOutputDeviceTab;
	struct ZLogRecord;

class WLogTab :public WTab
{

	ZOutputDeviceTab* LogTab = nullptr;

	std::string OutputCache;

	public:

	WLogTab(std::string inLabel);
	virtual ~WLogTab() override;
	void Tick(const float DeltaTime) override;

	protected:
		void DisplayLogToTab(const ZLogRecord& NewLog);
};

}
