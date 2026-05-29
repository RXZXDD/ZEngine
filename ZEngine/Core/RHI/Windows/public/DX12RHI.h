#pragma once

#include <wrl.h>
#include <memory>

#include "RHI/public/RHI.h"
#include "D3D12Device.h"
#include "DescriptorHeapManager.h"
#include "D3D12Texture.h"
#include "D3D12Viewport.h"
#include "D3D12Fence.h"

#include "RHI/public/RHIResources.h"

#include "Render/public/Shader/Shader.h"
#include <RHI/public/RHIBuffer.h>

struct IDXGIFactory4;
struct ID3D12CommandQueue;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct IDXGISwapChain;
struct ID3D12Resource;

enum DXGI_FORMAT;

namespace ZEngine::RHI
{

	class FDX12RHI : public IRHI
	{
		Microsoft::WRL::ComPtr<IDXGIFactory4> DxgiFactory;

		std::shared_ptr<FD3D12Device> Device;

		std::shared_ptr<FD3D12Fence> GpuFence;

		//todo need a swap chain class?
		int CurrBackBuffer = 0;

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

		//todo:merge to swapchain class
		FD3D12TextureRef SwapChainBuffer0;
		FD3D12TextureRef SwapChainBuffer1;
		FD3D12TextureRef DepthStencilBuffer;


		std::shared_ptr<FDescriptorHeapManager> DescriptorHeapMgr;

		HWND Wnd = nullptr;

		FD3D12Viewport Viewport;

		D3D12_RECT ScissorRect;

		std::unordered_map<std::string, std::shared_ptr<Render::FShader>> ShaderMap;

		Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignature;

		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>> PSOMap;


	public:

		//todo: move to scene renderer
		FRHITextureRef SceneTex;

		FDX12RHI(HWND InWND);

		virtual void Initialize() override;

		virtual void FlushCommandQueue() override;

		virtual void CloseCommandList() override;

		virtual void ExecuteCommandList() override;

		virtual void OnResize() override;

		virtual void CreateViewport(float TLX, float TLY, float w, float h, float MinD, float MaxD) override;
		
		void UpdateScissorRect(int InTLX, int InTLY, int InWidth, int InHeight);

		void CreateShaders();
		
		virtual void CreateRootSignature() override;

		virtual void CreatePipelineState() override;

		virtual FRHICommandAllocatorRef CreateCommandAllocator(ECommandListType InType) override;

		virtual FRHIBufferRef CreateBuffer(size_t elementSize, uint32 elementCount, bool isConstant = false) override;
		virtual void CommitResourceBuffer(FRHIBufferRef InBuffer, EHeapType HeapType) override;

		FRHITextureRef CreateTexture(const FRHITextureDesc& InDesc);
		void CommitResourceTexture(FRHITextureRef InTexture, EHeapType HeapType);


		virtual ID3D12Device* GetDevice();

		virtual ID3D12CommandQueue* GetCommandQueue();

		void Present();

		void ResizeWindow(UINT w, UINT h);

		//Getters
		FDescriptorHeapManager* GetDescriptorHeapMgr() const;

		IDXGISwapChain* GetSwapChain();

		ID3D12GraphicsCommandList* GetGraphicCommandList();

		ID3D12CommandAllocator* GetCommandAllocator();

		FD3D12Texture* GetCurrentBackBuffer();
		FD3D12Texture* GetStencilBuffer();



		ID3D12PipelineState* GetPSO(std::string_view InPSOName);

		/// <summary>
		/// todo: need a root signature manager to manage multiple root signatures, for now just return the default one
		/// </summary>
		/// <param name="InRootSignatureName"></param>
		/// <returns></returns>
		ID3D12RootSignature* GetRootSignature(const std::string_view& InRootSignatureName) const;

		FD3D12Viewport* GetD3D12Viewport();

		D3D12_RECT* GetScissorRect();

	protected:
		/// <summary>
		/// @todo remove from IRHI for not use for public
		/// </summary>
		virtual void EnableDebug() override;

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

		virtual void CreateGPUFence() override;

		virtual void CreateShaderResourceView() override;

		virtual void CreateUnorderedAccessView() override;


		FD3D12BufferRef CastBufferToD3D12Buffer(FRHIBufferRef InBuffer);
	};

	inline FDX12RHI* GetD3D12DynamicRHI()
	{
		return GetDynamicRHI<FDX12RHI>();
	}
}
