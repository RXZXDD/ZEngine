#include "D3D12CommandAllocator.h"

ZEngine::RHI::FD3D12CommandAllocator::~FD3D12CommandAllocator()
{
	if(CommandAllocator)
	{
		CommandAllocator->Release();
		CommandAllocator = nullptr;
	}
}
