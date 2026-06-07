#include "../public/Canvas.h"
#include <Render/public/GeometryGenerator.h>

FCanvas::FCanvas(int InX, int InY)
{
	Size.X = InX;
	Size.Y = InY;

}

FCanvas::FCanvas(const ZEngine::Render::FViewport& InViewport)
	:FCanvas((int)InViewport.Width, (int)InViewport.Height)
{

	float NCDWidth = Size.X / InViewport.Width;
	float NCDHeight = Size.Y / InViewport.Height;

	auto MeshData = ZEngine::Render::FGeometryGenerator::CreateQuad(
		LeftUp.X
		, LeftUp.Y
		, NCDWidth
		, NCDHeight
		, 0.f);
	CreateMesh(MeshData);
}
