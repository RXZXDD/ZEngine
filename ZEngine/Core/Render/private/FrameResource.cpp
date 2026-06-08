#include "../public/FrameResource.h"
#include "../public/ConstantBuffers.h"


#include "RHI/public/RHICommandAllocator.h"
#include "RHI/public/RHIDevice.h"
#include <RHI/public/RHIBuffer.h>
#include <RHI/public/RHI.h>


ZEngine::Render::FFrameResource::FFrameResource(uint32 PassCount, uint32 ObjcetCount)
{
	CmdAllocator = ZEngine::RHI::GDynamicRHI->CreateCommandAllocator(ECommandListType::DIRECT);

	ObjcetCB = ZEngine::RHI::GDynamicRHI->CreateBuffer(ObjcetCount, sizeof(ObjectConstantBuffer),true);

	ZEngine::RHI::GDynamicRHI->CommitResourceBuffer(ObjcetCB, EHeapType::UPLOAD);

	MainPassCB = ZEngine::RHI::GDynamicRHI->CreateBuffer(PassCount, sizeof(PassConstantBuffer), true);

	ZEngine::RHI::GDynamicRHI->CommitResourceBuffer(MainPassCB, EHeapType::UPLOAD);
}

ZEngine::RHI::FRHIBufferRef ZEngine::Render::FFrameResource::GetObjcetCB() const
{
	return ObjcetCB;
}

ZEngine::RHI::FRHIBufferRef ZEngine::Render::FFrameResource::GetMainPassCB() const
{
	return MainPassCB;
}
