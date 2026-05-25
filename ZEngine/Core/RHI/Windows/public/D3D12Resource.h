#pragma once

#include <memory>

#include "directx/d3d12.h"

#include "Core/Helper/public/ClassHelper.h"


namespace ZEngine::RHI
{
	/// <summary>
	/// manage the ID3DResource
	/// </summary>
	class FD3D12Resource
	{
		ID3D12Resource* Resource = nullptr;

	public:

		FD3D12Resource() = default;
		virtual ~FD3D12Resource();

		CTR_CP_DEL(FD3D12Resource);
		OP_ASSIGN_CP_DEL(FD3D12Resource);

		ID3D12Resource* Get() const;
		ID3D12Resource* GetResource() const;

		ID3D12Resource** GetAddressOf();
		ID3D12Resource* const* GetAddressOf() const;

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

	};

	using FD3D12ResourceRef = std::shared_ptr<FD3D12Resource>;
}
