#include "../public/D3D12MeshBuilder.h"

#include "Core/RHI/windows/public/D3D12MeshData.h"

#include "RHI/Windows/public/D3DUtils.h"
#include "Render/public/IDrawable.h"

//
//void ZEngine::RHI::FD3D12MeshBuilder::AddProxy(Render::FMeshProxy* const InProxy)
//{
//	Datas.push_back(InProxy);
//}

void ZEngine::RHI::FD3D12MeshBuilder::Build(std::vector<ZEngine::Render::IDrawable*>const& Datas, ID3D12Device* InDevice, ID3D12GraphicsCommandList* InCmdList)
{
	for (auto* Drawabke : Datas)
	{
		
		auto MeshData = Drawabke->GetProxy()->MeshData;
		std::vector<uint16> indices = MeshData.GetIndices16();


		Drawabke->GetProxy()->RHIMeshData = std::make_shared<FD3D12MeshData>();

		FD3D12MeshData* NativeData = (FD3D12MeshData*)Drawabke->GetProxy()->RHIMeshData->GetNativeMeshData();

		NativeData->CreateVertexBufferUpload((UINT)sizeof(ZEngine::Render::FVertex)
			, (UINT)MeshData.Vertices.size());

		NativeData->CreateIndexBufferUpload((UINT)sizeof(uint16)
			, (UINT)indices.size()
			, DXGI_FORMAT_R16_UINT);

		//create gpu resource
		D3DUtils::CreateDefaultBuffer(InDevice
			, InCmdList
			, MeshData.Vertices.data()
			, NativeData->GetVertexBufferUpload()->GetSize()
			, NativeData->GetVertexBufferGPU()
			, NativeData->GetVertexBufferUpload());

		D3DUtils::CreateDefaultBuffer(InDevice
			, InCmdList
			, indices.data()
			, NativeData->GetIndexBufferUpload()->GetSize()
			, NativeData->GetIndexBufferGPU()
			, NativeData->GetIndexBufferUpload());



		const UINT vbSize = (UINT)MeshData.Vertices.size() * (UINT)sizeof(ZEngine::Render::FVertex);
		NativeData->CreateVertexBlob(MeshData.Vertices.data(), vbSize);


		//todo: why from 32 to 16
		const UINT ibSize = (UINT)indices.size() * (UINT)sizeof(uint16);
		NativeData->CreateIndexBlob(indices.data(), ibSize);
		
		Drawabke->GetProxy()->BaseVertexLocation = 0;
		Drawabke->GetProxy()->StartIndexLocation = 0;
		Drawabke->GetProxy()->IndexCount = (UINT)indices.size();
		
	}
}
