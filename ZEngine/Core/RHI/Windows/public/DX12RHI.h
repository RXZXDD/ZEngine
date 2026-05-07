#pragma once

#include <wrl.h>
#include <memory>

#include "RHI/public/RHI.h"
#include "D3D12Device.h"
#include "DescriptorHeapManager.h"
#include "D3D12Texture.h"
#include "D3D12Viewport.h"


struct IDXGIFactory4;
struct ID3D12CommandQueue;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12Fence;
struct IDXGISwapChain;
struct ID3D12Device;
struct ID3D12Resource;

enum DXGI_FORMAT;

namespace ZEngine::RHI
{

	class FDX12RHI : public IRHI
	{
		Microsoft::WRL::ComPtr<IDXGIFactory4> DxgiFactory;

		//Microsoft::WRL::ComPtr<ID3D12Device> Device;
		std::shared_ptr<FD3D12Device> Device;

		Microsoft::WRL::ComPtr<ID3D12Fence> Fence;
		UINT64 CurrentFence = 0;

		int CurrBackBuffer = 0;

		std::unique_ptr<FDescriptorHeapManager> DescriptorHeapMgr;

		Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
		int SwapChainBufferCount = 0;
		//TODO: turn into texture type
		DXGI_FORMAT BackBufferFormat;
		DXGI_FORMAT DepthStencilFormat;

		UINT  m4xMsaaQuality = 0;
		bool m4xMsaaState = false;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> DirectCmdListAlloc;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList;

		//Microsoft::WRL::ComPtr<ID3D12Resource> SwapChainBuffer[2];
		FD3D12TextureRef SwapChainBuffer0;
		FD3D12TextureRef SwapChainBuffer1;


		//Microsoft::WRL::ComPtr<ID3D12Resource> DepthStencilBuffer;
		FD3D12TextureRef DepthStencilBuffer;


		HWND Wnd = nullptr;

		FD3D12Viewport Viewport;
	public:
		FDX12RHI(HWND InWND);

		virtual void Initialize() override;

		virtual void FlushCommandQueue() override;

		virtual void OnResize() override;

		virtual void CreateViewport(float TLX, float TLY, float w, float h, float MinD, float MaxD) override;
		virtual ID3D12Device* GetDevice();

		virtual ID3D12CommandQueue* GetCommandQueue();

		ID3D12DescriptorHeap* GetDescriptorHeap(EDescriptorHeapType InType);

		IDXGISwapChain* GetSwapChain();

		ID3D12GraphicsCommandList* GetGraphicCommandList();

		ID3D12CommandAllocator* GetCommandAllocator();

		ID3D12Resource* GetCurrentBackBuffer();
	protected:
		/// <summary>
		/// @todo remove from IRHI for not use for public
		/// </summary>
		virtual void EnableDebugLayer() override;

		void CreateDXGIFactory();

		virtual void CreateDevice() override;

		void MSAACheck();

		virtual void CreateCommandQueue() override;

		/// <summary>
		/// \brief Create 2 SwapChain RT and 1 DS
		/// </summary>
		void CreateSwapChainResource();

		virtual void CreateSwapChain(HWND InWND, int InWidth, int InHeight, int InCount, bool InWindowed = true) override;

		virtual void CreateDescriptorHeaps() override;

		virtual void Shutdown() override;

		virtual void CreateVertexShader() override;

		virtual void CreatePixelShader() override;

		virtual void CreateComputeShader() override;

		virtual void CreateRootSignature() override;

		virtual void CreatePipelineState() override;

		virtual void CreateGPUFence() override;

		virtual void CreateShaderResourceView() override;

		virtual void CreateUnorderedAccessView() override;

	};

	inline FDX12RHI* GetD3D12DynamicRHI()
	{
		return GetDynamicRHI<FDX12RHI>();
	}
}
