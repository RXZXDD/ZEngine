#include <memory>

#include "../public/RHIBuffer.h"
#include <cassert>


ZEngine::RHI::FRHIBuffer::FRHIBuffer(  size_t elementSize, uint32 elementCount, bool isConstant)
{

	Desc.ElementCount = elementCount;
	Desc.IsConstant = isConstant;
	if (isConstant)
	{
		Desc.ElementSize = CalcConstantBufferByteSize(elementSize);
	}
	else
	{
		Desc.ElementSize = elementSize;
	}
}

void ZEngine::RHI::FRHIBuffer::CopyData(int InIndex, const void * InData, size_t InDataSize)
{
	assert(false);
}
