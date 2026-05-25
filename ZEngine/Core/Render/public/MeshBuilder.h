#pragma once

#include <vector>

#include "Core/Render/public/Mesh.h"

namespace ZEngine::Render
{
	/// <summary>
	/// \brief this class job is to build the rhi resource for the given MeshData.
	/// inherit the method Build() to do the actual rhi platform
	/// </summary>
	class FMeshBuilder
	{
	protected:
		std::vector<FMeshProxy*> Datas;
		ERHIType Type = ERHIType::Unknown;
	public:
		FMeshBuilder(ERHIType InType);
		void AddMesh(FMeshProxy* const  InMeshDataPtr);
		virtual void Build() = 0;
	};
}
