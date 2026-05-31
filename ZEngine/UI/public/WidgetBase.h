#pragma once
#include <string>

namespace ZEngine
{
	class WWidgetBase {
	protected:
		std::string Label;
		bool bVisible = true;
	public:
		WWidgetBase() = default;
		virtual ~WWidgetBase() = default;
		virtual void Tick(const float DeltaTime) = 0;

		bool IsVisible() const { return bVisible; }
		void SetVisible(bool InVisible) { bVisible = InVisible; }
	};
}