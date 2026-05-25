#pragma once
#include "Core/Misc/public/PlatformTypeDef.h"
#include "Core/Render/public/Mesh.h"

namespace ZEngine::Render
{

	class FGeometryGenerator
	{
	public:

		/// <summary>
		///  Creates a quad aligned with the screen.  This is useful for postprocessing and screen effects.
		/// </summary>
		static FMeshData CreateQuad(float x, float y, float w, float h, float depth);
	};
}
