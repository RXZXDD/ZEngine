#include "../public/SceneRenderer.h"
#include "Render/public/IDrawable.h"
#include <RHI/Windows/public/DX12RHI.h>
#include <RHI/public/RHIGlobal.h>

#include "Render/public/FrameResource.h"

#include "Render/public/ConstantBuffers.h"

#include <DirectXMath.h>

#include "Core/GlobalCore.h"


namespace ZEngine::Render
{
	uint64 FSceneRenderer::CurrentFrame = 0;

	FSceneRenderer::FSceneRenderer()
	{
		MeshBuilder = std::make_unique<ZEngine::RHI::FD3D12MeshBuilder>();

		for (int i = 0; i < FRAME_RESOURCE_COUNT; ++i)
		{
			FrameResources.push_back(std::make_unique<FFrameResource>(
				1, 1));
		}


	}

	FSceneRenderer::FSceneRenderer(RHI::IRHI* InRHI)
		: FSceneRenderer()
	{
		pRHI = InRHI;
		ResizeSceneTex();
	
	}

	uint64 FSceneRenderer::UpdateViewportSize(const FFloatPoint& InSize)
	{
		Viewport.Width = InSize.X;
		Viewport.Height = InSize.Y;
		
		ResizeSceneTex();

		pRHI->UpdateSceneViewport(Viewport.Width, Viewport.Height);
		ZLOG(Renderer, Display, "viewport size updated: {}x{}", Viewport.Width, Viewport.Height);


		
		return pRHI->GetResourceSRVGPUHandle(SceneTex);
	}

	void FSceneRenderer::ResizeSceneTex()
	{
		RHI::FRHITextureDesc TexDesc;
		TexDesc.Format = EPixelFormat::PF_R8G8B8A8;
		TexDesc.Extent = FIntPoint{ (int)Viewport.Width, (int)Viewport.Height };
		TexDesc.Flags = TexCreate_RenderTargetable;

		SceneTex.reset();
		SceneTex = pRHI->CreateTexture(TexDesc);

		pRHI->CommitResourceTexture(SceneTex, EHeapType::DEFAULT);
	}

	void FSceneRenderer::AddDrawable(IDrawable* InDrawable)
	{
		Drawables.push_back(InDrawable);
		InDrawable->SetObjectIndex(Drawables.size() - 1);
		InDrawable->SetMaxFrameDirtyCount(FRAME_RESOURCE_COUNT);
		InDrawable->SetFrameDirtyCount(FRAME_RESOURCE_COUNT);
	}

	void FSceneRenderer::BuildProxyResource(ID3D12Device* InDevice, ID3D12GraphicsCommandList* InCmdList)
	{
		MeshBuilder->Build(Drawables, InDevice, InCmdList);
	}

	void FSceneRenderer::Draw(ID3D12GraphicsCommandList* InCmdList)
	{
		
		for (auto* Drawable : Drawables)
		{
			Drawable->Draw(InCmdList, *CurrentFrameResource);
		}
	}

	void FSceneRenderer::Start()
	{
		++CurrentFrame;
		CurrentFrameResource = GetCurrentFrameResource();
	}

	void FSceneRenderer::End()
	{

	}

	uint64 FSceneRenderer::GetCurrentFrame() const
	{
		return CurrentFrame;
	}
	FFrameResource* FSceneRenderer::GetCurrentFrameResource() const
	{
		return FrameResources[CurrentFrame % FRAME_RESOURCE_COUNT].get();
	}
	void FSceneRenderer::Update(float DeltaTime)
	{
		auto CB = CurrentFrameResource->GetObjcetCB();
		for (auto* pDrawable : Drawables)
		{
			if (pDrawable->IsDirty())
			{
				FFloatVector NewPosition = pDrawable->GetPosition();

				DirectX::XMMATRIX World = DirectX::XMMatrixTranslation(NewPosition.X, NewPosition.Y, NewPosition.Z);
				
				ObjectConstantBuffer ObjCB;

				DirectX::XMStoreFloat4x4(&ObjCB.World, XMMatrixTranspose(World));

				CB->CopyData(pDrawable->GetObjectIndex(), static_cast<void*>(&ObjCB), sizeof(ObjectConstantBuffer));

				pDrawable->DecreaseFrameDirtyCount();
			}
		}
	}
}
