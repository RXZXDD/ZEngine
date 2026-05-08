#include "../public/D3D12Fence.h"
#include "RHI/Windows/public/D3DUtils.h"


ZEngine::RHI::FD3D12Fence::~FD3D12Fence()
{
	if (Fence)
	{
		Fence->Release();
		Fence = nullptr;
	}
	CurrentFence = 0;
}

ZEngine::RHI::FD3D12Fence::FD3D12Fence(ID3D12Device* InDevice)
	: FRHIGPUFence("DX12Fence")
{
	ThrowIfFailed(InDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence)));

}

ID3D12Fence* ZEngine::RHI::FD3D12Fence::GetFence() const
{
	return Fence;
}

void ZEngine::RHI::FD3D12Fence::SetEventOnCompletion(HANDLE event)
{
	ThrowIfFailed(Fence->SetEventOnCompletion(CurrentFence, event));

}

bool ZEngine::RHI::FD3D12Fence::IsFenceComplete() const
{
	return Fence->GetCompletedValue() < CurrentFence;
}

UINT64 ZEngine::RHI::FD3D12Fence::Increase()
{
	return ++CurrentFence;
}
