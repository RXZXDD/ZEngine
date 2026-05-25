#pragma once
#include "directx/d3dx12.h"
#include "RHI/Windows/public/D3DUtils.h"

#include "RHI/public/RHIResources.h"
#include "RHI/Windows/public/D3D12Device.h"
#include "RHI/Windows/public/DescriptorHeapManager.h"

namespace ZEngine::RHI {


	class FD3D12Texture : public FRHITexture 
	{
		ID3D12Resource* Resource = nullptr;

		FHeapAllocator DescHeapAlloc;
		FHeapAllocator SRVDescHeapAlloc;

		D3D12_RENDER_TARGET_VIEW_DESC* RTVDesc = nullptr;

		DXGI_FORMAT DXFormat = DXGI_FORMAT_UNKNOWN;

		FFloatPoint Size{};

	protected:
		void SetUp();

	public:
		FD3D12Texture() = default;
		FD3D12Texture(FRHITextureDesc& InDesc, FD3D12Device* InDevice);

		~FD3D12Texture();
		
		D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle();
		D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle();
		D3D12_CPU_DESCRIPTOR_HANDLE GetView() const;

		DXGI_FORMAT GetFormat() const;
		FFloatPoint GetSize() const;

		void Reset();
		void ResetResource();

		ID3D12Resource* GetResource();
		ID3D12Resource** GetResourceAddress();

		FHeapAllocator* GetAllocator();
		FHeapAllocator* GetSRVAllocator();

		///
		/// Virtual functions implemented per RHI
		/// 

		/// <summary>
		/// @return platform-specific resource pointer
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeResource() const override
		{
			return Resource;
		}

		/// <summary>
		/// @return platform-specific SRV pointer
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeShaderResourceView() const
		{
			return nullptr;
		}

		/// <summary>
		/// @return platform-specific Texture baseclass
		/// </summary>
		/// <returns></returns>
		virtual void* GetTextureBaseRHI()
		{
			// Override this in derived classes to expose access to the native texture resource
			return nullptr;
		}
	};

	

	using FD3D12TextureRef = std::shared_ptr<FD3D12Texture>;


}
