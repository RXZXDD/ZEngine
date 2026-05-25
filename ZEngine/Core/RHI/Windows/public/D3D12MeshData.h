#pragma once

#include <string>

#include "directx/d3d12.h"

#include "RHI/public/RHIResources.h"
#include "RHI/Windows/public/D3D12Buffer.h"
#include "RHI/Windows/public/D3D12Blob.h"


namespace ZEngine::RHI
{
	class FD3D12MeshData :public FRHIMeshData
	{
		//use for look up
		std::string Name;

		//CPU copies
		FD3D12BlobRef VertexBufferCPU = nullptr;
		FD3D12BlobRef IndexBufferCPU = nullptr;

		//GPU resources for this mesh
		FD3D12BufferRef VertexBufferGPU = nullptr;
		FD3D12BufferRef IndexBufferGPU = nullptr;

		//use for upload to GPU default heap, can be release after create
		FD3D12BufferRef VertexBufferUpload = nullptr;
		FD3D12BufferRef IndexBufferUpload = nullptr;


	public:
		FD3D12MeshData();

		virtual void* GetNativeMeshData() override;

		FD3D12MeshData& CreateVertexBlob(void* InData, const UINT& InSize);
		FD3D12MeshData& CreateIndexBlob(void* InData, const UINT& InSize);

		FD3D12MeshData& CreateVertexBufferUpload(UINT InDataStride, UINT InDataNum, DXGI_FORMAT InFormat = DXGI_FORMAT_UNKNOWN);
		FD3D12MeshData& CreateIndexBufferUpload(UINT InDataStride, UINT InDataNum, DXGI_FORMAT InFormat = DXGI_FORMAT_UNKNOWN);

		FD3D12BufferRef GetVertexBufferGPU();
		FD3D12BufferRef GetIndexBufferGPU();

		FD3D12BufferRef GetVertexBufferUpload();
		FD3D12BufferRef GetIndexBufferUpload();

		D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() const;

		D3D12_INDEX_BUFFER_VIEW GetIndexBufferView()const;



	};
}
