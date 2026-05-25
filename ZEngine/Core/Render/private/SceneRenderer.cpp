#include "../public/SceneRenderer.h"
#include "Render/public/IDrawable.h"
#include <RHI/Windows/public/DX12RHI.h>
#include <RHI/public/RHIGlobal.h>

#include "Render/public/FrameResource.h"

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

	void FSceneRenderer::AddDrawable(IDrawable* InDrawable)
	{
		Drawables.push_back(InDrawable);
		InDrawable->SetObjectIndex(Drawables.size() - 1);
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
}
