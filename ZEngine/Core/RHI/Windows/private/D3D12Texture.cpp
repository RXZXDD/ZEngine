#include "../public/D3D12Texture.h"
#include "RHI/Windows/public/DescriptorHeapManager.h"


ZEngine::RHI::FD3D12Texture::FD3D12Texture(FRHITextureDesc& InDesc, FD3D12Device* InDevice)
	: FRHITexture()
{
	TextureDesc = InDesc;


	SetUp();

	if ((TextureDesc.Flags & TexCreate_RenderTargetable)== TexCreate_RenderTargetable)
	{
		auto HeapMgr = FDescriptorHeapManager::Get();
		HeapMgr->Allocate(EDescriptorHeapType::RTV, &HeapAlloc);
	}

	if ((TextureDesc.Flags & TexCreate_DepthStencilTargetable) == TexCreate_DepthStencilTargetable)
	{
		auto HeapMgr = FDescriptorHeapManager::Get();
		HeapMgr->Allocate(EDescriptorHeapType::DSV, &HeapAlloc);
	}

}

void ZEngine::RHI::FD3D12Texture::SetUp()
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

}

void ZEngine::RHI::FD3D12Texture::Reset()
{
	TextureDesc.Reset();
	Resource->Release();
}

void ZEngine::RHI::FD3D12Texture::ResetResource()
{
	Resource->Release();
	Resource = nullptr;
}

ZEngine::RHI::FD3D12Texture::~FD3D12Texture()
{
	if (Resource)
	{
		Resource->Release();
		Resource = nullptr;
	}
	auto HeapMgr = FDescriptorHeapManager::Get();

	
	HeapMgr->Free(EDescriptorHeapType::RTV, &HeapAlloc);
}

D3D12_CPU_DESCRIPTOR_HANDLE ZEngine::RHI::FD3D12Texture::GetCpuHandle()
{
	return HeapAlloc.CpuHandle;
}

D3D12_GPU_DESCRIPTOR_HANDLE ZEngine::RHI::FD3D12Texture::GetGpuHandle()
{
	return HeapAlloc.GpuHandle;
}

DXGI_FORMAT ZEngine::RHI::FD3D12Texture::GetFormat() const
{
	return DXFormat;
}
