#include "../public/D3D12Texture.h"
#include "RHI/Windows/public/DescriptorHeapManager.h"
#include <RHI/Windows/public/DX12RHI.h>


namespace ZEngine::RHI
{
	FD3D12Texture::FD3D12Texture(const FRHITextureDesc& InDesc, FD3D12Device* InDevice)
		: FRHITexture()
	{
		TextureDesc = InDesc;
		SetUp();

	}

	void FD3D12Texture::SetUp()
	{
		assert(TextureDesc.Flags > TexCreate_None);

		switch (TextureDesc.Format)
		{
		case EPixelFormat::PF_R8G8B8A8:
			DXFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;

		case EPixelFormat::PF_DepthStencil:
			DXFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
			break;
		default:
			break;
		}

		Size.X = TextureDesc.GetSize().X;
		Size.Y = TextureDesc.GetSize().Y;

	}

	void FD3D12Texture::Reset()
	{
		TextureDesc.Reset();
		ResetResource();
	}

	void FD3D12Texture::ResetResource()
	{
		if (Resource)
		{
			Resource->Release();
			Resource = nullptr;

		}
	}

	ID3D12Resource* FD3D12Texture::GetResource()
	{
		return Resource;
	}

	ID3D12Resource** FD3D12Texture::GetResourceAddress()
	{
		return &Resource;
	}

	FHeapAllocator* FD3D12Texture::GetAllocator()
	{
		return &DescHeapAlloc;
	}

	FHeapAllocator* FD3D12Texture::GetSRVAllocator()
	{
		return &SRVDescHeapAlloc;
	}

	FD3D12Texture::~FD3D12Texture()
	{

		auto* D3D12DynamicRHI = GetD3D12DynamicRHI();
		if (D3D12DynamicRHI)
		{
			D3D12DynamicRHI->DeAllocateDescHeap(DescHeapAlloc);
			D3D12DynamicRHI->DeAllocateDescHeap(SRVDescHeapAlloc);

		}
		if (Resource)
		{
			Resource->Release();
			Resource = nullptr;
		}
		
	}

	D3D12_CPU_DESCRIPTOR_HANDLE FD3D12Texture::GetCpuHandle()
	{
		return DescHeapAlloc.CpuHandle;
	}

	D3D12_GPU_DESCRIPTOR_HANDLE FD3D12Texture::GetGpuHandle()
	{
		return DescHeapAlloc.GpuHandle;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE FD3D12Texture::GetSRVCpuHandle()
	{
		return SRVDescHeapAlloc.CpuHandle;
	}

	D3D12_GPU_DESCRIPTOR_HANDLE FD3D12Texture::GetSRVGpuHandle()
	{
		return SRVDescHeapAlloc.GpuHandle;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE FD3D12Texture::GetView() const
	{
		return DescHeapAlloc.CpuHandle;
	}

	DXGI_FORMAT FD3D12Texture::GetFormat() const
	{
		return DXFormat;
	}

	FFloatPoint FD3D12Texture::GetSize() const
	{
		return Size;
	}
}


