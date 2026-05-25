#include "../public/Triangle.h"

#include "Core/Render/public/GeometryGenerator.h"

FTriangle::FTriangle()
{
	MeshProxy = std::make_shared<ZEngine::Render::FMeshProxy>();
	MeshProxy->MeshData = ZEngine::Render::FGeometryGenerator::CreateQuad(0.f,0.f, 800.f, 600.f, 0.f);
}
