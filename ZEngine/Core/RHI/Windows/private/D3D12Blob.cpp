#include "../public/D3D12Blob.h"

#include "RHI/Windows/public/D3DUtils.h"

namespace ZEngine::RHI
{
	FD3D12Blob::~FD3D12Blob()
	{
		if (Blob)
		{
			Blob->Release();
			Blob = nullptr;
		}
	}
	FD3D12Blob::FD3D12Blob(const UINT& InByteSize)
	{
		Create(InByteSize);
	}

	void FD3D12Blob::Create(const UINT& InByteSize)
	{
		ThrowIfFailed(D3DCreateBlob(InByteSize, &Blob));
	}
	void FD3D12Blob::CopyData(void* InData, const UINT& InByteSize)
	{
		CopyMemory(Blob->GetBufferPointer(), InData, InByteSize);
	}

	ID3DBlob** FD3D12Blob::GetAddressOf()
	{
		return &Blob;
	}

	void* FD3D12Blob::GetBufferPointer()
	{
		return Blob->GetBufferPointer();
	}

	SIZE_T FD3D12Blob::GetBufferSize()
	{
		return Blob->GetBufferSize();
	}


}

