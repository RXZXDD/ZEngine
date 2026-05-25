#pragma once

#include <vector>

#include "Core/Misc/public/PlatformTypeDef.h"
#include "Core/Misc/public/CombineType.h"

#include "Render/public/PrimitiveTopology.h"

#include "RHI/public/RHIResources.h"


namespace ZEngine::Render
{
	struct FVertex
	{
		FVertex() {}
		FVertex(
			const FFloatVector& p,
			const FFloatVector& n,
			const FFloatVector& t,
			const FFloatPoint& uv,
			const FFloatVector4& color) :
			Position(p),
			Normal(n),
			TangentU(t),
			TexC(uv),
			Color(color) {
		}
		FVertex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v,
			float cx = 0.f, float cy = 0.f, float cz = 0.f, float cw = 0.f
		) :
			Position(px, py, pz),
			Normal(nx, ny, nz),
			TangentU(tx, ty, tz),
			TexC(u, v),
			Color(cx, cy, cz, cw) {
		}

		FFloatVector Position;
		FFloatVector Normal;
		FFloatVector TangentU;
		FFloatVector4 Color;
		FFloatPoint TexC;
	};

	struct FMeshData
	{
		FMeshData() = default;
		std::vector<FVertex> Vertices;
		std::vector<uint32> Indices32;

		std::vector<uint16>& GetIndices16()
		{
			if (mIndices16.empty())
			{
				mIndices16.resize(Indices32.size());
				for (size_t i = 0; i < Indices32.size(); ++i)
					mIndices16[i] = static_cast<uint16>(Indices32[i]);
			}

			return mIndices16;
		}

	private:
		std::vector<uint16> mIndices16;
	};

	struct FMeshProxy
	{
		/// <summary>
		/// CPU data
		/// </summary>
		FMeshData MeshData;

		/// <summary>
		/// contain GPU useable resoures, craete from MeshData
		/// </summary>
		RHI::FRHIMeshDataRef RHIMeshData;

		//todo: abstract this struct
		EPrimitiveTopology PrimitiveType = EPrimitiveTopology::PT_TriangleList;

		uint32 IndexCount = 0;
		uint32 StartIndexLocation = 0;
		uint32 BaseVertexLocation = 0;
		uint32 StartInstanceLocation = 0;

	};
}
