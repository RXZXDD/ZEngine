#include "../public/Canvas.h"
#include <Render/public/GeometryGenerator.h>

FCanvas::FCanvas(int InX, int InY)
{
	Size.X = InX;
	Size.Y = InY;

}

FCanvas::FCanvas(int InX, int InY, const ZEngine::Render::FViewport& InViewport)
	:FCanvas(InX, InY)
{

	float NCDWidth = Size.X / InViewport.Width;
	float NCDHeight = Size.Y / InViewport.Height;
	CreateMesh(ZEngine::Render::FGeometryGenerator::CreateQuad(LeftUp.X
		, LeftUp.Y
		, NCDWidth
		, NCDHeight
		, 0.f));
}
