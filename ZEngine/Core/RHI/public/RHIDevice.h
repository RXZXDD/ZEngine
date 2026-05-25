#pragma once
#include "RHICommandList.h"


namespace ZEngine::RHI
{

	class FRHICommandAllocator;

	class FRHIDevice
	{
	public:

		virtual ~FRHIDevice() = default;

		virtual void CreateCommandAllocator(ECommandListType InCmdType, FRHICommandAllocator* InAllocator) = 0;
	};
}
