#pragma once

#include <iostream>

#ifndef UNIMPL
#define UNIMPL(x) \
	std::cerr << "Error in file: " << __FILE__  \
	<< " at line: " << __LINE__ \
	<< " in function: " << #x <<std::endl;
#endif // !1
