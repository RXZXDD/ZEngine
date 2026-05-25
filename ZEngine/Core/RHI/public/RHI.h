#pragma once

#include <memory>
#include <Windows.h>

#include "RHIResources.h"
#include "RHICommandAllocator.h"
#include "RHIBuffer.h"


namespace ZEngine::RHI
{


	/// <summary>
	/// @brief Interface for the Render Hardware Interface (RHI) in ZEngine. This interface defines the essential methods for initializing and managing the graphics device, command queues, swap chains, descriptor heaps, shaders, pipeline states, GPU fences, and resource views. Implementations of this interface will provide platform-specific functionality for rendering operations.
	/// </summary>
	class IRHI
	{
	public:
		virtual ~IRHI() = default;
		virtual void Initialize() = 0;
		virtual void OnResize() = 0;
		virtual void Shutdown() = 0;
		virtual void FlushCommandQueue() = 0;
		virtual void CloseCommandList() = 0;
		virtual void CreateViewport(float TLX, float TLY, float w, float h, float MinD, float MaxD)=0;



		virtual void EnableDebug() = 0;
		virtual void CreateDevice() = 0;
		virtual void CreateCommandQueue() = 0;
		virtual FRHICommandAllocatorRef CreateCommandAllocator(ECommandListType InType) = 0;
		virtual FRHIBufferRef CreateBuffer(size_t elementSize, uint32 elementCount, bool isConstant = false) = 0;
		virtual void CommitResource(FRHIBufferRef InBuffer, EHeapType HeapType) = 0;
		virtual void CreateSwapChain(HWND InWND, int InWidth, int InHeight, int InCount, bool InWindowed) = 0;
		virtual void CreateDescriptorHeaps() = 0;
		virtual void CreateVertexShader() = 0;
		virtual void CreatePixelShader() = 0;
		virtual void CreateComputeShader() = 0;
		virtual void CreateRootSignature() = 0;
		virtual void CreatePipelineState() = 0;
		virtual void CreateGPUFence() = 0;
		virtual void CreateShaderResourceView() = 0;
		virtual void CreateUnorderedAccessView() = 0;
	};


	extern std::shared_ptr<ZEngine::RHI::IRHI> GDynamicRHI;
	
	template<typename TRHI>
	inline TRHI* GetDynamicRHI()
	{
		return static_cast<TRHI*>(GDynamicRHI.get());
	}
}
