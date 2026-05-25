#pragma once

#include "directx/d3dx12.h"

#include "RHI/public/RHIResources.h"

namespace ZEngine::RHI
{
	class FD3D12Viewport : public FRHIViewport
	{
		D3D12_VIEWPORT Viewport;

	public:
		void SetAnchor(float x, float y);
		void Resize(float w, float h);
		void SetDepth(float Min, float Max);

		float GetWidth() const;
		float GetHeight() const;
		

		D3D12_VIEWPORT* GetViewport() const;

		FIntPoint GetExtent() const;
		FIntPoint GetAnchor() const;
	};

}
