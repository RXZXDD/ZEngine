#pragma once
#include <memory>

#include "directx/d3d12.h"

#include "Core/Helper/public/ClassHelper.h"

namespace ZEngine::RHI
{
	class FD3D12Blob 
	{
		ID3DBlob* Blob = nullptr;

	public:
		~FD3D12Blob();

		CTR_CP_DEL(FD3D12Blob);
		OP_ASSIGN_CP_DEL(FD3D12Blob);

		FD3D12Blob() = default;

		FD3D12Blob(const UINT& InByteSize);

		void Create(const UINT& InByteSize);

		void CopyData(void* InData, const UINT& InByteSize);
		
		ID3DBlob** GetAddressOf();

		/// <summary>
		/// wrapper of ID3DBlob::GetBufferPointer, return the pointer to the data buffer
		/// </summary>
		/// <returns></returns>
		void* GetBufferPointer();


		/// <summary>
		/// wrapper of ID3DBlob::GetBufferSize, return the size of the data buffer
		/// </summary>
		/// <returns></returns>
		SIZE_T GetBufferSize();
		

	};

	using FD3D12BlobRef = std::shared_ptr<FD3D12Blob>;
}
