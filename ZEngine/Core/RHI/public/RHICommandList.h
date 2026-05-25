#pragma once
#include <Misc/public/PlatformTypeDef.h>

#include "RHIDefinitions.h"

namespace ZEngine::RHI
{


	class FRHICommandList
	{

	public:
		ECommandListType GetType() const
		{
			return ECommandListType::UNKNOWN;
		}
	};
}


