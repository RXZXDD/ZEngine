#pragma once

#include <string>

#include "directx/d3d12.h"
#include <dxgi1_4.h>

#include "RHI/public/RHIBuffer.h"

#include "RHI/Windows/public/D3D12Resource.h"


#include "Core/Helper/public/ClassHelper.h"


namespace ZEngine::RHI
{

	class FD3D12Buffer : public FD3D12Resource , public FRHIBuffer
	{
	protected:

		DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN;

		byte* CpuData = nullptr;

	public:
		FD3D12Buffer() = default;

		FD3D12Buffer( size_t elementSize, uint32 elementCount, bool isConstant)
			: FRHIBuffer( elementSize, elementCount, isConstant)
		{
		}

		FD3D12Buffer( size_t elementSize, uint32 elementCount, bool isConstant, DXGI_FORMAT InFormat);

		virtual ~FD3D12Buffer() = default;
		CTR_CP_DEL(FD3D12Buffer);
		OP_ASSIGN_CP_DEL(FD3D12Buffer);

		void SetName(std::string InName);

		DXGI_FORMAT GetFormat() const;

		void SetFormat(DXGI_FORMAT InFormat) { Format = InFormat; }

		virtual void* GetNative() override
		{
			return this;
		}

		void InitCpuData();

		uint32 GetGPUVirtualAddressWithOffset(uint32 InOffset) const;

		virtual void CopyData(int InIndex, const void * InData, size_t InDataSize) override;

	};

	using FD3D12BufferRef = std::shared_ptr<FD3D12Buffer>;
}
