#pragma once
#include <string>

namespace ZEngine
{
	class WWidgetBase {
	protected:
		std::string _Label;
	public:
		WWidgetBase() = default;
		virtual ~WWidgetBase() = default;
		virtual void Tick(const float DeltaTime) = 0;
	};
}