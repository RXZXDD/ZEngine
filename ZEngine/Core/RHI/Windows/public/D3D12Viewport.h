#pragma once

#include "directx/d3dx12.h"

#include "RHI/public/RHIResources.h"

namespace ZEngine::RHI
{
	class FD3D12Viewport : public FRHIViewport
	{
		D3D12_VIEWPORT Viewport;
		D3D12_RECT ScissorRect;


	public:
		void SetAnchor(float x, float y);
		void SetDepth(float Min, float Max);

		/// <summary>
		/// resize viewport width and height, this will also update the scissor rect to match the viewport size.
		/// </summary>
		/// <param name="w"></param>
		/// <param name="h"></param>
		void Resize(float w, float h);
		void SetScissorRect(float InTLX, float InTLY, float InWidth, float InHeight);

		float GetWidth() const;
		float GetHeight() const;
		

		D3D12_VIEWPORT* GetViewport() const;

		FIntPoint GetExtent() const;
		FIntPoint GetAnchor() const;
		D3D12_RECT GetRect() const;

	};

}
