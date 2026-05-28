#pragma once

#include "Render/public/Renderer.h"

#include "RHI/Windows/public/D3D12MeshBuilder.h"

#include "Viewport.h"

namespace ZEngine::Render
{

	class IDrawable;

	class FFrameResource;

	/// <summary>
	/// @brief FSceneRenderer is responsible for rendering the scene, it will manage the render passes and the mesh proxies.
	/// </summary>
	class FSceneRenderer : public FRenderer
	{
		std::vector<IDrawable*> Drawables;
		std::unique_ptr<ZEngine::RHI::FD3D12MeshBuilder> MeshBuilder = nullptr;
		
		FFrameResource* CurrentFrameResource = nullptr;

		std::vector<std::unique_ptr<FFrameResource>> FrameResources;

		FViewport Viewport;

		/// <summary>
		/// represents total frames that have been rendered, it will be used for frame resource management and other time related logic.
		/// </summary>
		static uint64 CurrentFrame;

	public:
		virtual ~FSceneRenderer() = default;

		FSceneRenderer();

		void UpdateViewport(const FViewport& InViewport) { Viewport = InViewport; }

		FViewport GetViewport() const { return Viewport; }

		virtual void AddDrawable(IDrawable* InDrawable);

		void BuildProxyResource(ID3D12Device* InDevice, ID3D12GraphicsCommandList* InCmdList);

		virtual void Draw(ID3D12GraphicsCommandList* InCmdList);

		void Start();
		void End();
		//void AddMeshProxy(FMeshProxy* MeshProxy);

		uint64 GetCurrentFrame() const;

		/// <summary>
		/// return the current frame resource.
		/// </summary>
		/// <returns></returns>
		FFrameResource* GetCurrentFrameResource() const;

		/// <summary>
		/// Update the frame resource by time from GTimer.
		/// </summary>
		/// <param name="DeltaTime"></param>
		virtual void Update(float DeltaTime) override;


	};
}


