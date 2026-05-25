#include "../public/D3D12Device.h"

#include "RHI/public/RHIDefinitions.h"
#include <RHI/Windows/public/D3DUtils.h>
#include <RHI/Windows/public/D3D12CommandAllocator.h>

ZEngine::RHI::FD3D12Device::FD3D12Device(D3D_FEATURE_LEVEL level)
{
	//create hw
	HRESULT hardwareResult = D3D12CreateDevice(nullptr,
		level, IID_PPV_ARGS(&Device));
	FeatureLeve = level;

	//todo: if hardware result failed, try to create WARP device

}

ZEngine::RHI::FD3D12Device::~FD3D12Device()
{
	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
}

void ZEngine::RHI::FD3D12Device::CreateCommandAllocator(ECommandListType InCmdType, FRHICommandAllocator* InAllocator)
{
	auto D3D12CmdAllocator = static_cast<FD3D12CommandAllocator*>(InAllocator);
	ThrowIfFailed(
		GetDevice()->CreateCommandAllocator(
			D3DUtils::GetD3DCommandListType(InCmdType)
			, IID_PPV_ARGS(D3D12CmdAllocator->GetAddressOf())
		)
	);

}
