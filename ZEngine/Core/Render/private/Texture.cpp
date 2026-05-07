#include "../public/Texture.h"

#include "RHI/Windows/public/D3DUtils.h"
#include "Render/DDSTextureLoader.h"
#include "directx/d3dx12.h"
#include "Core/Misc/public/CombineType.h"
#include "RHI/Windows/public/DescriptorHeapManager.h"

void ZTexture::CreateResource(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList)
{
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(device, cmdList, FileName.c_str(), Resource, UploadHeap));
	//FDescriptorHeapManager::Get()->Allocate(device,EDescriptorHeapType::CBV_SRV_UAV, Resource.Get());
}

ID3D12Resource* ZTexture::GetResource() const
{
	return Resource.Get();
}

std::string_view ZTexture::GetName() const
{
	return Name;
}

FInt2 ZTexture::GetSize() const
{
	if (Resource)
	{
		auto desc = Resource->GetDesc();
		return FInt2(desc.Width, desc.Height);
	}
	return FInt2(0, 0);
}