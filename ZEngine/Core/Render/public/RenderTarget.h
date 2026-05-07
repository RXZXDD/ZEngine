#pragma once

#include <wrl.h>
#include "Render/public/TextureFormat.h"

#include "directx/d3dx12.h"

struct ID3D12Device;
struct ID3D12GraphicsCommandList;
struct ID3D12Resource;
struct CD3DX12_CPU_DESCRIPTOR_HANDLE;
struct CD3DX12_GPU_DESCRIPTOR_HANDLE;
struct FInt2;

class ZRenderTarget
{

	int Height = 0;

	int Width = 0;

	ETextureFormat Format = ETextureFormat::R8G8B8A8_UNORM;

	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;

	CD3DX12_CPU_DESCRIPTOR_HANDLE CpuHandle; // Index into the descriptor heap for RTV
	CD3DX12_GPU_DESCRIPTOR_HANDLE GpuHandle; // GPU handle for RTV

public:
	ZRenderTarget(int width, int height, ETextureFormat format = ETextureFormat::R8G8B8A8_UNORM)
		: Width(width), Height(height), Format(format)
	{
	}

	void CreateResource(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	FInt2 GetSize() const;

};