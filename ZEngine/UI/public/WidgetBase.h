#pragma once
#include <string>

class WWidgetBase {
	protected:
	std::string _Label;
	public:
	WWidgetBase() = default;
	virtual ~WWidgetBase() = default;
	virtual void Update() = 0;
};