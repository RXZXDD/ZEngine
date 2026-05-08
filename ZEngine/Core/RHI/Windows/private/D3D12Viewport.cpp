#include "../public/D3D12Viewport.h"

void ZEngine::RHI::FD3D12Viewport::SetAnchor(float x, float y)
{
	Viewport.TopLeftX = x;
	Viewport.TopLeftY = y;

	TopLeftX = x;
	TopLeftY = y;
}

void ZEngine::RHI::FD3D12Viewport::Resize(float w, float h)
{
	Viewport.Height = h;
	Viewport.Width = w;

	Height = h;
	Width = w;
}

void ZEngine::RHI::FD3D12Viewport::SetDepth(float Min, float Max)
{
	Viewport.MinDepth = Min;
	Viewport.MaxDepth = Max;

	MinDepth = Min;
	MaxDepth = Max;
}

float ZEngine::RHI::FD3D12Viewport::GetWidth() const
{
	return Viewport.Width;
}

float ZEngine::RHI::FD3D12Viewport::GetHeight() const
{
	return Viewport.Height;
}

FIntPoint ZEngine::RHI::FD3D12Viewport::GetExtent() const
{
	return FIntPoint(GetWidth(), GetHeight());
}
