#include "../public/DX12RHI.h"

#include "RHI/Windows/public/DescriptorHeapManager.h"
#include "Core/GlobalCore.h"

#include "directx/d3dx12.h"
#include "RHI/Windows/public/D3DUtils.h"
#include <RHI/Windows/public/D3D12Shader.h>
#include <RHI/Windows/public/D3D12Sampler.h>
#include <RHI/Windows/public/D3D12CommandAllocator.h>

namespace ZEngine::RHI
{
	FDX12RHI::FDX12RHI(HWND InWND): Wnd(InWND)
	{
		ZLOG(RHI, Display, "init dx12 rhi...");
		assert(Wnd);
		
	}

	FDX12RHI::~FDX12RHI()
	{
		//ZLOG(RHI, Display, "shut down dx12 rhi...");

	}

	void FDX12RHI::Initialize()
	{

		EnableDebug();

		CreateDXGIFactory();

		CreateDevice();

		CreateGPUFence();

		CreateDescriptorHeaps();

		//MSAACheck();

		CreateCommandQueue();

		CreateSwapChainResource();

		CreateSwapChain(Wnd, GetWindowViewport()->GetWidth(), GetWindowViewport()->GetHeight(), 2);

		FlushCommandQueue();
		
	}
	void FDX12RHI::FlushCommandQueue()
	{
		assert(CommandQueue);
		assert(CommandList);
		assert(DirectCmdListAlloc);

		;

		ThrowIfFailed(CommandQueue->Signal(GpuFence->GetFence(), GpuFence->Increase()));

		//wait until fence complete
		if (GpuFence->IsFenceComplete())
		{
			HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);

			GpuFence->SetEventOnCompletion(eventHandle);

			//block
			WaitForSingleObject(eventHandle, INFINITE);
			CloseHandle(eventHandle);
		}
	}

	void FDX12RHI::CloseCommandList()
	{
		assert(CommandList);
		ThrowIfFailed(CommandList->Close());
	}

	void FDX12RHI::ExecuteCommandList()
	{
		assert(CommandList);
		assert(CommandQueue);
		ID3D12CommandList* cmdsLists[] = { CommandList.Get() };
		CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
		FlushCommandQueue();
	}
	void FDX12RHI::OnResize()
	{
		assert(Device);
		assert(SwapChain);
		assert(DirectCmdListAlloc);

		FlushCommandQueue();

		ThrowIfFailed(CommandList->Reset(DirectCmdListAlloc.Get(), nullptr));

		//RT DS resize
		SwapChainBuffer0->ResetResource();
		SwapChainBuffer1->ResetResource();

		ThrowIfFailed(SwapChain->ResizeBuffers(SwapChainBufferCount,
			GetWindowViewport()->GetWidth(),
			GetWindowViewport()->GetHeight(),
			BackBufferFormat,
			DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

		CurrBackBuffer = 0;

		//Reset RT
		ThrowIfFailed(SwapChain->GetBuffer(0, IID_PPV_ARGS(SwapChainBuffer0->GetResourceAddress())));

		auto d = SwapChainBuffer0->GetResource()->GetDesc();

		GetDevice()->CreateRenderTargetView(SwapChainBuffer0->GetResource()
											, nullptr
											, SwapChainBuffer0->GetCpuHandle());

		ThrowIfFailed(SwapChain->GetBuffer(1, IID_PPV_ARGS(SwapChainBuffer1->GetResourceAddress())));

		GetDevice()->CreateRenderTargetView(SwapChainBuffer1->GetResource()
			, nullptr
			, SwapChainBuffer1->GetCpuHandle());

		//Reset DS
		DepthStencilBuffer->ResetResource();

		D3D12_RESOURCE_DESC depthStencilDesc;
		depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		depthStencilDesc.Alignment = 0;
		depthStencilDesc.Width = GetWindowViewport()->GetWidth();
		depthStencilDesc.Height = GetWindowViewport()->GetHeight();
		depthStencilDesc.DepthOrArraySize = 1;
		depthStencilDesc.MipLevels = 1;

		depthStencilDesc.Format = DepthStencilFormat;

		depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
		depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;


		D3D12_CLEAR_VALUE optClear;
		optClear.Format = DepthStencilFormat;
		optClear.DepthStencil.Depth = 1.0f;
		optClear.DepthStencil.Stencil = 0;

		auto heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		ThrowIfFailed(Device->GetDevice()->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&depthStencilDesc,
			D3D12_RESOURCE_STATE_COMMON,
			&optClear,
			IID_PPV_ARGS(DepthStencilBuffer->GetResourceAddress())
		));

		Device->GetDevice()->CreateDepthStencilView(
			DepthStencilBuffer->GetResource(),
			nullptr,
			DepthStencilBuffer->GetCpuHandle()
		);

		auto transition =
			CD3DX12_RESOURCE_BARRIER::Transition(
				DepthStencilBuffer->GetResource(),
				D3D12_RESOURCE_STATE_COMMON,
				D3D12_RESOURCE_STATE_DEPTH_WRITE
			);

		CommandList->ResourceBarrier(1,
			&transition);

		ThrowIfFailed(CommandList->Close());
		//ZLOG(RHI, Display, "command list closed");
		ID3D12CommandList* cmdLists[] = { CommandList.Get() };
		CommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

		FlushCommandQueue();

	}

	void FDX12RHI::CreateViewport(float TLX, float TLY, float w, float h, float MinD, float MaxD)
	{
		FD3D12Viewport NewVP;
		NewVP.SetAnchor(TLX, TLY);
		NewVP.SetDepth(MinD, MaxD);
		NewVP.Resize(w, h);


		Viewports.push_back(NewVP);

	}

	FD3D12Viewport* FDX12RHI::GetWindowViewport()
	{
		//todo : use ifdef Editor to chang WindowViewport Index
		return &Viewports[0];
	}

	FD3D12Viewport* FDX12RHI::GetSceneViewport()
	{
		//todo : use ifdef Editor to chang SceneViewport Index
		if(Viewports.size() < 2)
		{
			return nullptr;
		}
		return &Viewports[1];
	}

	void FDX12RHI::UpdateSceneViewport(float InWidth, float InHeight)
	{
		auto SceneVP = GetSceneViewport();
		if(!SceneVP)
		{
			CreateViewport(0, 0, InWidth, InHeight, 0.f, 1.f);
			SceneVP = GetSceneViewport();
		}

		SceneVP->Resize(InWidth, InHeight);
	}

	void FDX12RHI::CreateShaders()
	{
		//regist shaders
		std::shared_ptr<Render::FCanvasVS> cvs = std::make_shared<Render::FCanvasVS>();
		std::shared_ptr<Render::FCanvasPS> cps = std::make_shared<Render::FCanvasPS>();
		ShaderMap[cvs->GetName()] = cvs;
		ShaderMap[cps->GetName()] = cps;


		std::for_each(ShaderMap.begin(), ShaderMap.end(),
			[](const auto& pair)
			{
				pair.second->Compile();
			});

	}

	void FDX12RHI::DeAllocateDescHeap(FHeapAllocator& InAllocator)
	{
		auto* DescriptorHeapMgr = GetDescriptorHeapMgr();
		if(InAllocator.HeapType != EDescriptorHeapType::Undefined && DescriptorHeapMgr)
			DescriptorHeapMgr->Free(InAllocator.HeapType, &InAllocator);
	}

	ID3D12Device* FDX12RHI::GetDevice()
	{
		assert(Device != nullptr && "GetDevice not init");
		return Device->GetDevice();
	}

	ID3D12CommandQueue* FDX12RHI::GetCommandQueue()
	{
		return CommandQueue.Get();
	}

	void FDX12RHI::Present()
	{
		GetSwapChain()->Present(1, 0);
		CurrBackBuffer = (CurrBackBuffer + 1) % SwapChainBufferCount;

	}

	void FDX12RHI::ResizeWindow(UINT w, UINT h)
	{
		if (w != 0 || h != 0)
		{
			GetWindowViewport()->Resize(w, h);
			OnResize();
		}
	}

	FDescriptorHeapManager* FDX12RHI::GetDescriptorHeapMgr() const
	{
		if (DescriptorHeapMgr.get() == nullptr)
		{
			assert(false && "GetDescriptorHeapMgr not init");
		}
		return DescriptorHeapMgr.get();
	}



	IDXGISwapChain* FDX12RHI::GetSwapChain()
	{
		return SwapChain.Get();
	}

	ID3D12GraphicsCommandList* FDX12RHI::GetGraphicCommandList()
	{
		return CommandList.Get();
	}

	ID3D12CommandAllocator* FDX12RHI::GetCommandAllocator()
	{
		return DirectCmdListAlloc.Get();
	}

	FD3D12Texture* FDX12RHI::GetCurrentBackBuffer()
	{
		return CurrBackBuffer == 0 ? SwapChainBuffer0.get() : SwapChainBuffer1.get();
	}

	FD3D12Texture* FDX12RHI::GetStencilBuffer()
	{
		return DepthStencilBuffer.get();
	}

	ID3D12PipelineState* ZEngine::RHI::FDX12RHI::GetPSO(std::string_view InPSOName)
	{
		auto it = PSOMap.find(std::string(InPSOName));
		if (it != PSOMap.end())
		{
			return it->second.Get();
		}
		return nullptr;
	}

	ID3D12RootSignature* FDX12RHI::GetRootSignature(const std::string_view& InRootSignatureName) const
	{
		return RootSignature.Get();
	}

	FD3D12Viewport* FDX12RHI::GetD3D12Viewport(size_t index) 
	{
		return index < Viewports.size() ? &Viewports[index] : nullptr;
	}


	void FDX12RHI::EnableDebug()
	{
		#if defined(DEBUG) || defined(_DEBUG)
				{
					Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
					ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
					debugController->EnableDebugLayer();
				}
		#endif
	}


	void FDX12RHI::CreateDXGIFactory()
	{
		ThrowIfFailed(::CreateDXGIFactory(IID_PPV_ARGS(&DxgiFactory)));
	}

	void FDX12RHI::CreateDevice()
	{
		Device = std::make_shared<FD3D12Device>(D3D_FEATURE_LEVEL_11_0);
		
		//create hw
		//HRESULT hardwareResult = D3D12CreateDevice(nullptr,
		//	D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&Device));

		//Fallback to WARP device
		/*if (FAILED(hardwareResult))
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter> pWarpAdapter;
			ThrowIfFailed(DxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));

			ThrowIfFailed(D3D12CreateDevice(pWarpAdapter.Get(),
				D3D_FEATURE_LEVEL_11_0,
				IID_PPV_ARGS(&Device)));
		}*/

	}

	void FDX12RHI::MSAACheck()
	{
		//4xMSAA check
		D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
		msQualityLevels.Format = BackBufferFormat;
		msQualityLevels.SampleCount = 4;
		msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
		msQualityLevels.NumQualityLevels = 0;
		ThrowIfFailed(GetDevice()->CheckFeatureSupport(
			D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
			&msQualityLevels,
			sizeof(msQualityLevels)
		));
		m4xMsaaQuality = msQualityLevels.NumQualityLevels;
		assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level.");
	}

	void FDX12RHI::CreateCommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		ThrowIfFailed(GetDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&CommandQueue)));

		ThrowIfFailed(GetDevice()->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			IID_PPV_ARGS(DirectCmdListAlloc.GetAddressOf())));

		ThrowIfFailed(GetDevice()->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			DirectCmdListAlloc.Get(),
			nullptr,
			IID_PPV_ARGS(CommandList.GetAddressOf())));

		//CommandList->Close();
	}

	void FDX12RHI::CreateSwapChainResource()
	{
		FRHITextureDesc TexDesc;
		TexDesc.Format = EPixelFormat::PF_R8G8B8A8;
		TexDesc.Extent = GetWindowViewport()->GetExtent();
		TexDesc.Flags = TexCreate_RenderTargetable;

		SwapChainBuffer0 = std::make_shared<FD3D12Texture>(TexDesc, Device.get());
		GetDescriptorHeapMgr()->Allocate(EDescriptorHeapType::RTV, SwapChainBuffer0->GetAllocator());

		SwapChainBuffer1 = std::make_shared<FD3D12Texture>(TexDesc, Device.get());
		GetDescriptorHeapMgr()->Allocate(EDescriptorHeapType::RTV, SwapChainBuffer1->GetAllocator());


		TexDesc.Format = EPixelFormat::PF_DepthStencil;
		TexDesc.Flags = TexCreate_DepthStencilTargetable;
		DepthStencilBuffer = std::make_shared<FD3D12Texture>(TexDesc, Device.get());
		GetDescriptorHeapMgr()->Allocate(EDescriptorHeapType::DSV, DepthStencilBuffer->GetAllocator());

		BackBufferFormat = SwapChainBuffer0->GetFormat();
		DepthStencilFormat = DepthStencilBuffer->GetFormat();
	}

	void FDX12RHI::CreateSwapChain(HWND InWND, int InWidth, int InHeight,int InCount,bool InWindowed)
	{
		SwapChain.Reset();

		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = InWidth;
		sd.BufferDesc.Height = InHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = BackBufferFormat;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		sd.SampleDesc.Count = m4xMsaaState ? 4 : 1;
		sd.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		SwapChainBufferCount = InCount;
		sd.BufferCount = SwapChainBufferCount;

		sd.OutputWindow = InWND;

		sd.Windowed = InWindowed;

		sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		ThrowIfFailed(DxgiFactory->CreateSwapChain(
			CommandQueue.Get(),
			&sd,
			SwapChain.GetAddressOf()));

	}

	void FDX12RHI::CreateDescriptorHeaps()
	{
		DescriptorHeapMgr = std::make_shared<FDescriptorHeapManager>(GetDevice());
	}

	void FDX12RHI::Shutdown()
	{
	}

	void FDX12RHI::CreateVertexShader()
	{
	}

	void FDX12RHI::CreatePixelShader()
	{
	}

	void FDX12RHI::CreateComputeShader()
	{
	}

	void FDX12RHI::CreateRootSignature()
	{
		//todo: auto build root signature by shader reflection
		
		// Root parameter can be a table, root descriptor or root constants.
		CD3DX12_ROOT_PARAMETER slotRootParameter[3];

		// Perfomance TIP: Order from most frequent to least frequent.\
		
		//objcb slot
		slotRootParameter[0].InitAsConstantBufferView(0);
		
		//Main Pass CB slot
		slotRootParameter[1].InitAsConstantBufferView(1);
		
		//tex slot
		slotRootParameter[2].InitAsShaderResourceView(0, 1);
		//slotRootParameter[3].InitAsDescriptorTable(1, &texTable, D3D12_SHADER_VISIBILITY_ALL);

		auto staticSamplers = FD3D12SamplerFactory::GetStaticSamplers();

		// A root signature is an array of root parameters.
		CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(_countof(slotRootParameter), slotRootParameter,
			(UINT)staticSamplers.size(), staticSamplers.data(),
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
		FD3D12BlobRef serializedRootSig = std::make_shared<FD3D12Blob>();
		FD3D12BlobRef errorBlob = std::make_shared<FD3D12Blob>();
		HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
			serializedRootSig->GetAddressOf(), errorBlob->GetAddressOf());

		if (hr != S_OK)
		{
			::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
		ThrowIfFailed(hr);

		ThrowIfFailed(GetDevice()->CreateRootSignature(
			0,
			serializedRootSig->GetBufferPointer(),
			serializedRootSig->GetBufferSize(),
			IID_PPV_ARGS(RootSignature.GetAddressOf())));
	}

	void FDX12RHI::CreatePipelineState()
	{
		using namespace ZEngine::Render;
		FD3D12VertexShader* VSShader = (FD3D12VertexShader*)ShaderMap["CanvasVS"].get();
		FD3D12PixelShader* PSShader = (FD3D12PixelShader*)ShaderMap["CanvasPS"].get();

		D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;

		ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		opaquePsoDesc.InputLayout = { VSShader->GetInputLayout().data(), (UINT)VSShader->GetInputLayout().size()};
		opaquePsoDesc.pRootSignature = RootSignature.Get();
		opaquePsoDesc.VS =
		{
			reinterpret_cast<BYTE*>(VSShader->GetCodeBufferPointer()),
			VSShader->GetCodeBufferSize()
		};
		opaquePsoDesc.PS =
		{
			reinterpret_cast<BYTE*>(PSShader->GetCodeBufferPointer()),
			PSShader->GetCodeBufferSize()
		};
		opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		opaquePsoDesc.SampleMask = UINT_MAX;
		opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		opaquePsoDesc.NumRenderTargets = 1;
		opaquePsoDesc.RTVFormats[0] = BackBufferFormat;
		opaquePsoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
		opaquePsoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
		opaquePsoDesc.DSVFormat = DepthStencilFormat;

		ThrowIfFailed(GetDevice()->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&PSOMap["opaque"])));

	}

	FRHICommandAllocatorRef FDX12RHI::CreateCommandAllocator(ECommandListType InType)
	{
		assert(InType != ECommandListType::UNKNOWN && "CommandList Type Unknown");

		auto D3DCommandListType = D3DUtils::GetD3DCommandListType(InType);
		std::shared_ptr<FD3D12CommandAllocator> ret = std::make_shared<FD3D12CommandAllocator>();
		ThrowIfFailed(GetDevice()->CreateCommandAllocator(
			D3DCommandListType,
			IID_PPV_ARGS(ret->GetAddressOf())));
		return FRHICommandAllocatorRef{ret};
	}

	FRHIBufferRef FDX12RHI::CreateBuffer(size_t elementSize, uint32 elementCount, bool isConstant)
	{
		std::shared_ptr<FD3D12Buffer> ret = std::make_shared<FD3D12Buffer>(elementSize, elementCount, isConstant);

		return ret;
	}

	FRHITextureRef FDX12RHI::CreateTexture(const FRHITextureDesc& InDesc)
	{
		std::shared_ptr<FD3D12Texture> ret = std::make_shared<FD3D12Texture>(InDesc, Device.get());
		//todo: should alloc desc heap here?
		GetDescriptorHeapMgr()->Allocate(EDescriptorHeapType::RTV, ret->GetAllocator());
		GetDescriptorHeapMgr()->Allocate(EDescriptorHeapType::CBV_SRV_UAV, ret->GetSRVAllocator());


		return ret;
	}

	void FDX12RHI::CommitResourceTexture(FRHITextureRef InTexture, EHeapType HeapType)
	{
		FD3D12Texture* pD3DTex = static_cast<FD3D12Texture*>(InTexture.get());
		
		auto heapProperty = CD3DX12_HEAP_PROPERTIES(D3DUtils::GetD3DHeapType(HeapType));
		auto resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			pD3DTex->GetFormat(),
			pD3DTex->GetSize().X,
			pD3DTex->GetSize().Y,
			1,
			0,
			1,
			0,
			D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

		auto optClear = CD3DX12_CLEAR_VALUE(pD3DTex->GetFormat()
			, pD3DTex->GetClearColor().data());

		ThrowIfFailed(GetDevice()->CreateCommittedResource(
			&heapProperty,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_COMMON,
			&optClear,
			IID_PPV_ARGS(pD3DTex->GetResourceAddress())
		));
		CreateRenderTargetView(InTexture);
		CreateShaderResourceView(InTexture);

	}

	void FDX12RHI::CreateRenderTargetView(FRHITextureRef InTexture)
	{
		FD3D12Texture* InTexPtr = static_cast<FD3D12Texture*>(InTexture.get());

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = InTexPtr->GetFormat();
		//todo: abstract params
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D = { 0,0 };

		GetDevice()->CreateRenderTargetView(InTexPtr->GetResource()
			, nullptr
			, InTexPtr->GetCpuHandle());
	}

	void FDX12RHI::CommitResourceBuffer(FRHIBufferRef InBuffer, EHeapType HeapType)
	{
		FD3D12Buffer* bInBuffer = (FD3D12Buffer*)InBuffer->GetNative();

		auto heapProperty = CD3DX12_HEAP_PROPERTIES(D3DUtils::GetD3DHeapType(HeapType));

		auto bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(InBuffer->GetSize());
		ThrowIfFailed(GetDevice()->CreateCommittedResource(
			&heapProperty,
			D3D12_HEAP_FLAG_NONE,
			&bufferDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(bInBuffer->GetAddressOf())
		));

		if (HeapType == EHeapType::UPLOAD)
		{
			bInBuffer->InitCpuData();

		}
	}

	void FDX12RHI::CreateGPUFence()
	{
		GpuFence = std::make_shared<FD3D12Fence>(GetDevice());
	}

	void FDX12RHI::CreateShaderResourceView(FRHITextureRef InTexture)
	{

		FD3D12Texture* InTexPtr = static_cast<FD3D12Texture*>(InTexture.get());

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = InTexPtr->GetFormat();
		//todo: param abstraction
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = -1;

		GetDevice()->CreateShaderResourceView(InTexPtr->GetResource()
			, &srvDesc
			, InTexPtr->GetSRVAllocator()->CpuHandle);

	}

	uint64 FDX12RHI::GetResourceSRVGPUHandle(FRHITextureRef InTexture)
	{
		FD3D12Texture* InTexPtr = static_cast<FD3D12Texture*>(InTexture.get());
	
		return InTexPtr->GetSRVGpuHandle().ptr;
	}

	void FDX12RHI::CreateUnorderedAccessView()
	{
	}
	FD3D12BufferRef FDX12RHI::CastBufferToD3D12Buffer(FRHIBufferRef InBuffer)
	{
		return std::dynamic_pointer_cast<FD3D12Buffer>(InBuffer);
	}
}
