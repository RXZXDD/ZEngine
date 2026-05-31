#pragma once
#include "Core/Render/public/IDrawable.h"
#include "Core/Render/public/Viewport.h"

class FCanvas : public ZEngine::Render::IDrawable
{
	FIntPoint Size = FIntPoint{ 0,0 };
	FFloatPoint LeftUp = FFloatPoint{ -1.f,1.0f };
public:
	FCanvas(int InX, int InY);
	FCanvas(const ZEngine::Render::FViewport& InViewport);
};