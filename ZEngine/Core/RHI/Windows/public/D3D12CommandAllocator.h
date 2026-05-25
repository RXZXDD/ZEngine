#pragma once

#include "directx/d3dx12.h"

#include "RHI/public/RHICommandAllocator.h"

#include "Core/Helper/public/ClassHelper.h"


namespace ZEngine::RHI
{

	/// <summary>
	/// wrapper class for ID3D12CommandAllocator, which is used to allocate memory for command lists. 
	/// </summary>
	class FD3D12CommandAllocator : public FRHICommandAllocator
	{
		ID3D12CommandAllocator* CommandAllocator = nullptr;

	public:
		FD3D12CommandAllocator() = default;
		virtual ~FD3D12CommandAllocator();

		CTR_CP_DEL(FD3D12CommandAllocator);
		OP_ASSIGN_CP_DEL(FD3D12CommandAllocator);


		virtual void* GetNativeCommandAllocator() const override
		{
			return CommandAllocator;
		}

		ID3D12CommandAllocator* Get() const
		{
			return CommandAllocator;
		}

		ID3D12CommandAllocator** GetAddressOf()
		{
			return &CommandAllocator;
		}
	};
}
