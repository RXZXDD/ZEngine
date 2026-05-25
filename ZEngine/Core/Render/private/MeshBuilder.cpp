#include "../public/MeshBuilder.h"

#include "Core/GlobalCore.h"
#include "Logger/public/LoggerMacro.h"

ZEngine::Render::FMeshBuilder::FMeshBuilder(ERHIType InType)
{
	switch (InType)
	{
	case ERHIType::DX12:
		Type = InType;
		break;

	default:
		ZLOG(RHI, Fatal, "Unknown RHI");
		break;
	}
}

void ZEngine::Render::FMeshBuilder::AddMesh(FMeshProxy* const InMeshDataPtr)
{
	Datas.push_back(InMeshDataPtr);
}
