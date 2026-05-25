#pragma once
#include <memory>

#include "Core/Helper/public/ClassHelper.h"

#include "RHIDefinitions.h"


namespace ZEngine::RHI
{

	class FRHIDevice;

	class FRHICommandAllocator
	{
	public:

		CTR_CP_DEL(FRHICommandAllocator);
		OP_ASSIGN_CP_DEL(FRHICommandAllocator);

		FRHICommandAllocator() = default;
		virtual void* GetNativeCommandAllocator() const;
	};

	using FRHICommandAllocatorRef = std::shared_ptr<FRHICommandAllocator>;
}
