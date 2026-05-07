#pragma once

#include "Render/public/Renderer.h"

namespace ZEngine::Render
{
	/// <summary>
	/// @brief FSceneRenderer is responsible for rendering the scene, it will manage the render passes and the mesh proxies.
	/// </summary>
	class FSceneRenderer : public FRenderer
	{
		//std::vector<FMeshProxy*> MeshProxies;

	public:
		virtual ~FSceneRenderer() = default;

		///
		virtual void Initialize(RHI::IRHI* InRHI);

		virtual void Draw();

		void Start();
		void End();
		//void AddMeshProxy(FMeshProxy* MeshProxy);



	};
}


