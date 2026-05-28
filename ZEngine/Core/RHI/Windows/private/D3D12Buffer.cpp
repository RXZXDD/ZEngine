#include "../public/D3D12Buffer.h"

#include "RHI/Windows/public/D3DUtils.h"

namespace ZEngine::RHI
{

	FD3D12Buffer::FD3D12Buffer(size_t elementSize, uint32 elementCount, bool isConstant, DXGI_FORMAT InFormat)
		:ZEngine::RHI::FD3D12Buffer::FD3D12Buffer( elementSize, elementCount, isConstant)
	{
		Format = InFormat;
	}

	void FD3D12Buffer::SetName(std::string InName)
	{
		this->Get()->SetName(std::wstring(InName.begin(), InName.end()).c_str());
	}

	DXGI_FORMAT ZEngine::RHI::FD3D12Buffer::GetFormat() const
	{

		return Format;
	}
	void FD3D12Buffer::InitCpuData()
	{
		ThrowIfFailed(GetResource()->Map(0, nullptr, reinterpret_cast<void**>(&CpuData)));

	}
	uint32 FD3D12Buffer::GetGPUVirtualAddressWithOffset(uint32 InOffset) const
	{
		assert(InOffset < -1);
		return Get()->GetGPUVirtualAddress() + InOffset* GetElementSize();
	}
	void FD3D12Buffer::CopyData(int InIndex, const void * InData, size_t InDataSize)
	{
		assert(CpuData != nullptr && "CpuData not initialized, call InitCpuData first");
		memcpy(&CpuData[InIndex * GetElementSize()], InData, InDataSize);
	}
}


