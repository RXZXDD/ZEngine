#include "../public/GeometryGenerator.h"

namespace ZEngine::Render
{
	FMeshData FGeometryGenerator::CreateQuad(float x, float y, float w, float h, float depth)
	{
		FMeshData meshData;

		meshData.Vertices.resize(4);
		meshData.Indices32.resize(6);

		// Position coordinates specified in NDC space.
		meshData.Vertices[0] = FVertex(
			x, y - h, depth,
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f);

		meshData.Vertices[1] = FVertex(
			x, y, depth,
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f);

		meshData.Vertices[2] = FVertex(
			x + w, y, depth,
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f);

		meshData.Vertices[3] = FVertex(
			x + w, y - h, depth,
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f);

		meshData.Indices32[0] = 0;
		meshData.Indices32[1] = 1;
		meshData.Indices32[2] = 2;

		meshData.Indices32[3] = 0;
		meshData.Indices32[4] = 2;
		meshData.Indices32[5] = 3;

		return meshData;
	}

}
