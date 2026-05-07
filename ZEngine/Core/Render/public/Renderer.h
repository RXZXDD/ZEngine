#pragma once

#include <vector>

#include "RHI/public/RHI.h"

namespace ZEngine::Render
{
	class FRenderer
	{
		RHI::IRHI* RHI = nullptr;

	public:
		virtual ~FRenderer() = default;

		virtual void Initialize(RHI::IRHI* InRHI) = 0;

		virtual void Draw() = 0;

	};
}


