#pragma once
#include <vector>

#include "directx/d3d12.h"


namespace ZEngine::Render
{
	class IDrawable;
}

namespace ZEngine::RHI
{



	class FD3D12MeshBuilder 
	{
		//std::vector<Render::FMeshProxy*> Datas;

	public:
		//void AddProxy(Render::FMeshProxy* const InProxy);
		void Build(std::vector<ZEngine::Render::IDrawable*> const & Datas,ID3D12Device* InDevice, ID3D12GraphicsCommandList* InCmdList) ;
	};
}
