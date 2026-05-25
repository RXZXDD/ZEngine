#pragma once

#include <vector>

#include "directx/d3d12.h"

#include "RHI/public/RHI.h"

namespace ZEngine::Render
{

	class IDrawable;

	class FRenderer
	{

	public:
		virtual ~FRenderer() = default;

		virtual void AddDrawable(IDrawable* InDrawable) = 0;

		virtual void Draw(ID3D12GraphicsCommandList* InCmdList) = 0;

	};
}


