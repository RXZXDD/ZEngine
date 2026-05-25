#pragma once

#include "Core/Render/public/PrimitiveTopology.h"
#include <d3d12.h>

namespace ZEngine::RHI
{
	/// <summary>
	/// Helper Class to get true type associate with the DX12
	/// </summary>
	class FD3D12PrimitiveTopology
	{
	public:
		static D3D12_PRIMITIVE_TOPOLOGY GetRHIPrimitiveTopology(Render::EPrimitiveTopology InPT);
	};
}
