#pragma once
#include <memory>
#include "Core/Helper/public/ClassHelper.h"

#include "RHI/public/RHIDefinitions.h"

#include "RHI/public/RHICommandAllocator.h"
#include "RHI/public/RHIBuffer.h"



namespace ZEngine::Render
{

	class FFrameResource
	{
		uint64 Fence = 0;

		RHI::FRHIBufferRef ObjcetCB = nullptr;

		RHI::FRHICommandAllocatorRef CmdAllocator = nullptr;

		public:

		CTR_CP_DEL(FFrameResource);
		OP_ASSIGN_CP_DEL(FFrameResource);

		FFrameResource(uint32 PassCount, uint32 ObjcetCount);


		~FFrameResource() = default;

		RHI::FRHIBufferRef GetObjcetCB() const;
	};

}
