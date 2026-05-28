#include "../public/D3D12MeshData.h"

#include "RHI/Windows/public/D3DUtils.h"

namespace ZEngine::RHI
{
	FD3D12MeshData::FD3D12MeshData()
	{
		Name = "test";

		VertexBufferCPU = std::make_shared<FD3D12Blob>();
		IndexBufferCPU = std::make_shared<FD3D12Blob>();

		VertexBufferGPU = std::make_shared<FD3D12Buffer>();
		IndexBufferGPU = std::make_shared<FD3D12Buffer>();
		

	}
	void* FD3D12MeshData::GetNativeMeshData()
	{
		return this;
	}
	FD3D12MeshData& ZEngine::RHI::FD3D12MeshData::CreateVertexBlob(void* InData, const UINT& InSize)
	{
		VertexBufferCPU = std::make_shared<FD3D12Blob>(InSize);
		VertexBufferCPU->CopyData(InData, InSize);
		return *this;
	}

	FD3D12MeshData& ZEngine::RHI::FD3D12MeshData::CreateIndexBlob(void* InData, const UINT& InSize)
	{
		IndexBufferCPU = std::make_shared<FD3D12Blob>(InSize);
		IndexBufferCPU->CopyData(InData, InSize);
		return *this;
	}

	FD3D12MeshData& FD3D12MeshData::CreateVertexBufferUpload(UINT InDataStride, UINT InDataNum, DXGI_FORMAT InFormat)
	{
		VertexBufferUpload = std::make_shared<ZEngine::RHI::FD3D12Buffer>(InDataStride, InDataNum,false,  InFormat);
	
		return *this;
	}

	FD3D12MeshData& FD3D12MeshData::CreateIndexBufferUpload(UINT InDataStride, UINT InDataNum, DXGI_FORMAT InFormat)
	{
		IndexBufferUpload = std::make_shared<ZEngine::RHI::FD3D12Buffer>(InDataStride, InDataNum,false,  InFormat);
		
		return *this;
	}

	FD3D12BufferRef FD3D12MeshData::GetVertexBufferGPU()
	{
		return VertexBufferGPU;
	}

	FD3D12BufferRef FD3D12MeshData::GetIndexBufferGPU()
	{
		return IndexBufferGPU;
	}

	FD3D12BufferRef FD3D12MeshData::GetVertexBufferUpload()
	{
		return VertexBufferUpload;
	}

	FD3D12BufferRef FD3D12MeshData::GetIndexBufferUpload()
	{
		return IndexBufferUpload;
	}

	D3D12_VERTEX_BUFFER_VIEW ZEngine::RHI::FD3D12MeshData::GetVertexBufferView() const
	{
		D3D12_VERTEX_BUFFER_VIEW ret;
		ret.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
		ret.SizeInBytes = VertexBufferGPU->GetSize();
		ret.StrideInBytes = VertexBufferGPU->GetElementSize();
		return ret;
	}

	D3D12_INDEX_BUFFER_VIEW ZEngine::RHI::FD3D12MeshData::GetIndexBufferView()const
	{
		D3D12_INDEX_BUFFER_VIEW ret;
		ret.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
		ret.Format = IndexBufferGPU->GetFormat();
		ret.SizeInBytes = IndexBufferGPU->GetSize();
		return ret;
	}

}



