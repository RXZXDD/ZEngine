#pragma once
#include <string>

#include "../public/WidgetBase.h"

namespace ZEngine
{
	class WTab :public WWidgetBase
	{
	public:
		WTab(std::string inLabel);
		virtual ~WTab();
		void Tick(const float DeltaTime) override;


	};
}