#pragma once
#include "directx/d3dx12.h"

class FD3D12Device{
	ID3D12Device* Device = nullptr;
	D3D_FEATURE_LEVEL FeatureLeve;
public:
	FD3D12Device(D3D_FEATURE_LEVEL level);
	~FD3D12Device();

	ID3D12Device* GetDevice()  {
		return Device;
	}

};
