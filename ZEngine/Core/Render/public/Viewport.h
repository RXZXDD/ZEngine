#pragma once

namespace ZEngine::Render
{
	struct FViewport
	{
		float TLX = 0.f;
		float TLY = 0.f;
		float Width = 1.f;
		float Height = 1.f;
		float MinDepth = 0.f;
		float MaxDepth = 1.f;
		FViewport() = default;
		FViewport(float InTLX, float InTLY, float InWidth, float InHeight, float InMinDepth = 0.f, float InMaxDepth = 1.f)
			: TLX(InTLX), TLY(InTLY), Width(InWidth), Height(InHeight), MinDepth(InMinDepth), MaxDepth(InMaxDepth)
		{
		}
	};
}
