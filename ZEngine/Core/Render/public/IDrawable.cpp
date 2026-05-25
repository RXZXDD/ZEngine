#include "IDrawable.h"



#include "RHI/Windows/public/D3D12MeshData.h"

#include "RHI/Windows/public/D3D12PrimitiveTopology.h"
#include "FrameResource.h"


namespace ZEngine::Render
{
    FMeshProxy* IDrawable::GetProxy() const
    {
        return MeshProxy.get();
    }

    void IDrawable::CreateMesh(FMeshData& InData, EPrimitiveTopology InPT)
    {
        MeshProxy = std::make_shared<FMeshProxy>();
        MeshProxy->PrimitiveType = InPT;
        MeshProxy->MeshData = InData;
    }

    void IDrawable::Draw(ID3D12GraphicsCommandList* InCmdList, const FFrameResource& InFrameResource)
    {
        auto* DX12MeshData = (ZEngine::RHI::FD3D12MeshData*)MeshProxy->RHIMeshData->GetNativeMeshData();
        InCmdList->IASetVertexBuffers(0, 1, &DX12MeshData->GetVertexBufferView());
        InCmdList->IASetIndexBuffer(&DX12MeshData->GetIndexBufferView());
        InCmdList->IASetPrimitiveTopology(RHI::FD3D12PrimitiveTopology::GetRHIPrimitiveTopology(MeshProxy->PrimitiveType));

        auto* D3D12ObjectCB = static_cast<ZEngine::RHI::FD3D12Buffer*>(InFrameResource.GetObjcetCB().get());

		//todo:create a static int num in RootSignature and use it to set root parameter, avoid hard code 0
        InCmdList->SetGraphicsRootConstantBufferView(0
            , D3D12ObjectCB->GetGPUVirtualAddressWithOffset(GetObjectIndex()));

        InCmdList->DrawIndexedInstanced(MeshProxy->IndexCount
            , 1
            , MeshProxy->StartIndexLocation
            , MeshProxy->BaseVertexLocation
            , MeshProxy->StartInstanceLocation);
    }

    uint32 IDrawable::GetObjectIndex() const
    {
        assert(ObjectIndex != -1 && "Objcet Index not set");
        return ObjectIndex;
    }
    void IDrawable::SetObjectIndex(uint32 InIndex)
    {
        ObjectIndex = InIndex;
    }

}
