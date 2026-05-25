#pragma once
#include "directx/d3dx12.h"

#include "RHI/public/RHIDevice.h"

namespace ZEngine::RHI
{
	class FD3D12Device : public FRHIDevice
	{
		ID3D12Device* Device = nullptr;
		D3D_FEATURE_LEVEL FeatureLeve;
	public:
		FD3D12Device(D3D_FEATURE_LEVEL level);
		~FD3D12Device();

		ID3D12Device* GetDevice() {
			return Device;
		}


		// 通过 FRHIDevice 继承
		void CreateCommandAllocator(ECommandListType InCmdType, FRHICommandAllocator* InAllocator) override;

	};

}

