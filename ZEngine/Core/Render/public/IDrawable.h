#pragma once

#include "Core/Render/public/Mesh.h"

#include "Render/public/PrimitiveTopology.h"

#include <d3d12.h>

namespace ZEngine::Render
{

	class FFrameResource;
	/// <summary>
	/// all things can be draw should be inherit.
	/// </summary>
	class IDrawable
	{
	protected:
		std::shared_ptr<FMeshProxy> MeshProxy = nullptr;

		/// <summary>
		/// use to index the object constant buffer in frame resource
		/// </summary>
		uint32 ObjectIndex = -1;

	public:

		void CreateMesh(FMeshData& InData, EPrimitiveTopology InPT = EPrimitiveTopology::PT_TriangleList);

		/// <summary>
		/// todo: abstract D3DCommandlist
		/// </summary>
		/// <param name="InCmdList"></param>
		/// <param name="InFrameResource"></param>
		void Draw(ID3D12GraphicsCommandList* InCmdList, const FFrameResource& InFrameResource);

		FMeshProxy* GetProxy()const;

		uint32 GetObjectIndex() const;

		void SetObjectIndex(uint32 InIndex);
	};
}
