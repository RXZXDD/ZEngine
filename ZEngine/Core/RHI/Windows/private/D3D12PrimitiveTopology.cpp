#include "../public/D3D12PrimitiveTopology.h"

//todo: move GLOG to LoggerMacro?
#include "Core/GlobalCore.h"
#include "Logger/public/LoggerMacro.h"

D3D12_PRIMITIVE_TOPOLOGY ZEngine::RHI::FD3D12PrimitiveTopology::GetRHIPrimitiveTopology(Render::EPrimitiveTopology InPT)
{
	switch (InPT)
	{
	case ZEngine::Render::EPrimitiveTopology::PT_TriangleList:
		return  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case ZEngine::Render::EPrimitiveTopology::PT_UNKNOWN:
	default:
		ZLOG(RHI, Fatal, "Unkown Primitive Topology type")
		break;
	}
	return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
}
