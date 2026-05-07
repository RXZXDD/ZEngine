#pragma once

#include "Core/Helper/public/ClassHelper.h"

#include <cstdint>
#include <string>

namespace ZEngine {

	struct ZLogRecord;
	enum class LogLevel : uint8_t;

	class ZBaseLogger
	{
		ZBaseLogger() = delete;
		CTR_CP_RM(ZBaseLogger)

	protected:
		std::string Name;

	public:
		ZBaseLogger(std::string InName);
		
		ZLogRecord Serialize(const LogLevel LogLevel, const std::string Msg);



		std::string_view GetName() const { return Name; }
	};



}