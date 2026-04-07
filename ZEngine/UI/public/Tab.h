#pragma once
#include <string>

#include "../public/WidgetBase.h"

namespace ZEngine
{
	class WTab :public WWidgetBase
	{
	public:
		WTab(std::string inLabel);
		~WTab();
		void Update() override;

		void ProcessLogic();
	};
}