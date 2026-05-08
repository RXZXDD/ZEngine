#pragma once
#include "directx/d3dx12.h"

#include "RHI/public/RHIResources.h"



namespace ZEngine::RHI
{
	class FD3D12Fence : public FRHIGPUFence
	{
		UINT64 CurrentFence = 0;
		ID3D12Fence* Fence = nullptr;
	public:
		~FD3D12Fence();
		FD3D12Fence(ID3D12Device* InDevice);

		ID3D12Fence* GetFence() const;

		void SetEventOnCompletion(HANDLE event);

		bool IsFenceComplete() const;

		UINT64 Increase();
	};
}
