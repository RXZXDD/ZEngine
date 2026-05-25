#include "../public/D3D12Resource.h"


namespace ZEngine::RHI
{
	FD3D12Resource::~FD3D12Resource()
	{
		if (Resource)
		{
			Resource->Release();
			Resource = nullptr;
		}
	}

	ID3D12Resource* FD3D12Resource::Get() const
	{
		return Resource;
	}

	ID3D12Resource* FD3D12Resource::GetResource() const
	{
		return Resource;
	}
	
	ID3D12Resource** FD3D12Resource::GetAddressOf()
	{
		return &Resource;
	}

	ID3D12Resource* const* FD3D12Resource::GetAddressOf() const
	{
		return &Resource;
	}

	D3D12_GPU_VIRTUAL_ADDRESS FD3D12Resource::GetGPUVirtualAddress() const
	{
		return Resource->GetGPUVirtualAddress();
	}

}