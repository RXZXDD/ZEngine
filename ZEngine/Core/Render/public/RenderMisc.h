#pragma once

#include <stdint.h>

namespace ZEngine::Render
{
	enum class ERenderPassType : uint8_t
	{
		Forward,
		Deferred,
		ShadowMap,
		PostProcess,
		UI,
		Count
	};

	enum class ERenderQueue : uint8_t
	{
		Background,
		Geometry,
		AlphaTest,
		Transparent,
		Overlay,
		Count
	};
}
