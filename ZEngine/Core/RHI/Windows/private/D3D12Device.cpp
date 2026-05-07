#include "../public/D3D12Device.h"

FD3D12Device::FD3D12Device(D3D_FEATURE_LEVEL level)
{
	//create hw
	HRESULT hardwareResult = D3D12CreateDevice(nullptr,
		level, IID_PPV_ARGS(&Device));
	FeatureLeve = level;

}

FD3D12Device::~FD3D12Device()
{
	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
}
