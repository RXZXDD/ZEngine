#include "../public/DescriptorHeapManager.h"
#include "Core/GlobalCore.h"

#include <cassert>
#include <iostream>

#include "directx/d3dx12.h"
#include "RHI/Windows/public/D3DUtils.h"

#include "Core/Misc/public/DevHelper.h"

std::unordered_map<std::string, DescriptorHeapBlock> FDescriptorHeapManager::DescriptorHeaps = {};


void DescriptorHeapBlock::CreateHeapRTV(ID3D12Device* InDevice)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = Capacity;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;

	ThrowIfFailed(InDevice->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(Heap.GetAddressOf())));
	Heap->SetName(L"Heap_RT");

	HeapStartCpu = Heap->GetCPUDescriptorHandleForHeapStart();
	//HeapStartGpu = Heap->GetGPUDescriptorHandleForHeapStart();
}

void DescriptorHeapBlock::CreateHeapDSV(ID3D12Device* InDevice)
{
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = Capacity;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;

	ThrowIfFailed(InDevice->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(Heap.GetAddressOf())));
	Heap->SetName(L"DSV");

	HeapStartCpu = Heap->GetCPUDescriptorHandleForHeapStart();

}

void DescriptorHeapBlock::CreateHeapCBVSRVUAV(ID3D12Device* InDevice)
{
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = Capacity;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	ThrowIfFailed(InDevice->CreateDescriptorHeap(
		&srvHeapDesc, IID_PPV_ARGS(Heap.GetAddressOf())));
	Heap->SetName(L"CBV_SRV_UAV");

	HeapStartCpu = Heap->GetCPUDescriptorHandleForHeapStart();
	HeapStartGpu = Heap->GetGPUDescriptorHandleForHeapStart();
}

FDescriptorHeapManager::FDescriptorHeapManager(ID3D12Device* InDevice)
{
	RtvDescriptorSize = InDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	DsvDescriptorSize = InDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	CbvSrvUavDescriptorSize = InDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	DescriptorHeaps.emplace("RTV", DescriptorHeapBlock(RTV_NUM
		, EDescriptorHeapType::RTV
		, RtvDescriptorSize));
	DescriptorHeaps.emplace("DSV", DescriptorHeapBlock(DSV_NUM
		, EDescriptorHeapType::DSV
		, DsvDescriptorSize));
	DescriptorHeaps.emplace("CBV_SRV_UAV", DescriptorHeapBlock(CBV_NUM
		, EDescriptorHeapType::CBV_SRV_UAV
		, CbvSrvUavDescriptorSize));

	//create Heap
	DescriptorHeaps.at("RTV").CreateHeapRTV(InDevice);
	DescriptorHeaps.at("DSV").CreateHeapDSV(InDevice);
	DescriptorHeaps.at("CBV_SRV_UAV").CreateHeapCBVSRVUAV(InDevice);

	ZLOG(RHI, Display, "------FDescriptorHeapManager inited-------");
}

void FDescriptorHeapManager::Allocate(EDescriptorHeapType type, FHeapAllocator* InAllocator)
{
	std::string typeName;
	int descriptorSize = 0;
	switch (type) {
	case EDescriptorHeapType::RTV:
		typeName = "RTV";
		descriptorSize = RtvDescriptorSize;
		break;
	case EDescriptorHeapType::DSV:
		typeName = "DSV";
		descriptorSize = DsvDescriptorSize;
		break;
	case EDescriptorHeapType::CBV_SRV_UAV:
		typeName = "CBV_SRV_UAV";
		descriptorSize = CbvSrvUavDescriptorSize;
	default:
		assert(false);
	}

	auto& heapBlock = DescriptorHeaps.at(typeName);

	return heapBlock.Allocate(InAllocator);
}

void FDescriptorHeapManager::Free(EDescriptorHeapType type, FHeapAllocator* InAllocator)
{
	std::string typeName;
	int descriptorSize = 0;
	switch (type) {
	case EDescriptorHeapType::RTV:
		typeName = "RTV";
		descriptorSize = RtvDescriptorSize;
		break;
	case EDescriptorHeapType::DSV:
		typeName = "DSV";
		descriptorSize = DsvDescriptorSize;
		break;
	case EDescriptorHeapType::CBV_SRV_UAV:
		typeName = "CBV_SRV_UAV";
		descriptorSize = CbvSrvUavDescriptorSize;
	default:
		assert(false);
	}

	auto& heapBlock = DescriptorHeaps.at(typeName);

	return heapBlock.Free(InAllocator);
}

D3D12_CPU_DESCRIPTOR_HANDLE FDescriptorHeapManager::GetCpuHandle(EDescriptorHeapType type, int InIdx)
{
	std::string typeName;
	int descriptorSize = 0;
	ID3D12DescriptorHeap* TargetHeap = nullptr;
	
	switch (type) {
	case EDescriptorHeapType::RTV:
		typeName = "RTV";
		descriptorSize = RtvDescriptorSize;
		break;
	case EDescriptorHeapType::DSV:
		typeName = "DSV";
		descriptorSize = DsvDescriptorSize;
		break;
	case EDescriptorHeapType::CBV_SRV_UAV:
		typeName = "CBV_SRV_UAV";
		descriptorSize = CbvSrvUavDescriptorSize;
		break;
	default:
		assert(false);
	}

	return DescriptorHeaps.at(typeName).GetCpuHandle(InIdx);
}

D3D12_GPU_DESCRIPTOR_HANDLE FDescriptorHeapManager::GetGpuHandle(EDescriptorHeapType type, int InIdx)
{
	std::string typeName;
	int descriptorSize = 0;
	ID3D12DescriptorHeap* TargetHeap = nullptr;

	switch (type) {
	case EDescriptorHeapType::RTV:
		typeName = "RTV";
		descriptorSize = RtvDescriptorSize;
		break;
	case EDescriptorHeapType::DSV:
		typeName = "DSV";
		descriptorSize = DsvDescriptorSize;
		break;
	case EDescriptorHeapType::CBV_SRV_UAV:
		typeName = "CBV_SRV_UAV";
		descriptorSize = CbvSrvUavDescriptorSize;
		break;
	default:
		assert(false);
	}

	return DescriptorHeaps.at(typeName).GetGpuHandle(InIdx);
}

ID3D12DescriptorHeap* FDescriptorHeapManager::GetRawHeap(EDescriptorHeapType InType)
{
	std::string typeName;

	switch (InType) {
	case EDescriptorHeapType::RTV:
		typeName = "RTV";
		break;
	case EDescriptorHeapType::DSV:
		typeName = "DSV";
		break;
	case EDescriptorHeapType::CBV_SRV_UAV:
		typeName = "CBV_SRV_UAV";
		break;
	default:
		assert(false && "Unknown EDescriptorHeapType");
	}
	return DescriptorHeaps.at(typeName).Heap.Get();
}

void FDescriptorHeapManager::ImGUISrvAllocFn(D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_desc_handle)
{
	auto HeapBlock = DescriptorHeaps.at("CBV_SRV_UAV");
	HeapBlock.Allocate(out_cpu_desc_handle, out_gpu_desc_handle);

}

void FDescriptorHeapManager::ImGUISrvFreeFn(D3D12_CPU_DESCRIPTOR_HANDLE out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE out_gpu_desc_handle)
{
	auto HeapBlock = DescriptorHeaps.at("CBV_SRV_UAV");
	HeapBlock.Free(out_cpu_desc_handle, out_gpu_desc_handle);
}


void DescriptorHeapBlock::Allocate(FHeapAllocator* InAllocator)
{
	assert(Offset < Capacity);

	InAllocator->DescriptorSize = DescriptorSize;
	InAllocator->HeapType = Type;
	InAllocator->CpuHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE{ HeapStartCpu , Offset , DescriptorSize };
	InAllocator->GpuHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE{ HeapStartGpu , Offset , DescriptorSize };
	++Offset;

}

void DescriptorHeapBlock::Free(FHeapAllocator* InAllocator)
{
	int cpu_idx = (int)((InAllocator->CpuHandle.ptr - HeapStartCpu.ptr) / DescriptorSize);
	int gpu_idx = (int)((InAllocator->GpuHandle.ptr - HeapStartGpu.ptr) / DescriptorSize);
	assert(cpu_idx == gpu_idx);
	--Offset;
}



void DescriptorHeapBlock::Allocate(D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_desc_handle)
{
	assert(Offset < Capacity);
	int idx = Offset;

	CD3DX12_CPU_DESCRIPTOR_HANDLE CpuHeapHandle{ HeapStartCpu ,Offset, DescriptorSize };
	out_cpu_desc_handle->ptr = CpuHeapHandle.ptr;

	CD3DX12_GPU_DESCRIPTOR_HANDLE GpuHeapHandle{ HeapStartGpu ,Offset, DescriptorSize };
	out_gpu_desc_handle->ptr = GpuHeapHandle.ptr;

	++Offset;
}

void DescriptorHeapBlock::Free(D3D12_CPU_DESCRIPTOR_HANDLE out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE out_gpu_desc_handle)
{
	int cpu_idx = (int)((out_cpu_desc_handle.ptr - HeapStartCpu.ptr) / DescriptorSize);
	int gpu_idx = (int)((out_gpu_desc_handle.ptr - HeapStartGpu.ptr) / DescriptorSize);
	assert(cpu_idx == gpu_idx);
	--Offset;
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapBlock::GetCpuHandle(int InOffset)
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE{HeapStartCpu, InOffset, DescriptorSize};
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapBlock::GetGpuHandle(int InOffset)
{
	return CD3DX12_GPU_DESCRIPTOR_HANDLE{ HeapStartGpu, InOffset, DescriptorSize };

}
