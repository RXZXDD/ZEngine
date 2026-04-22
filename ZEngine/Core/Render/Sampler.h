#pragma once

#include "directx/d3dx12.h"
#include <array>


class SamplerFactory
{
public:
	static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();
};
