#pragma once
#include <wrl.h>
#include <unordered_map>
#include <string>
#include <cassert>
#include <queue>

#include "Logger/public/LoggerMacro.h"

#include "directx/d3dx12.h"

#define RTV_NUM 10
#define DSV_NUM 1
#define CBV_NUM 5000


DECLARE_LOGGER_EXTERN(RenderLog);


struct DescriptorHeapBlock;

/// <summary>
/// \todo put into single file?
/// </summary>
enum class EDescriptorHeapType :uint8_t
{
	RTV,
	DSV,
	CBV_SRV_UAV,
	Undefined
};

struct FHeapAllocator {
	UINT DescriptorSize = 0;
	EDescriptorHeapType HeapType = EDescriptorHeapType::Undefined;
	D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle;

	FHeapAllocator() = default;
	~FHeapAllocator() = default;

};


struct DescriptorHeapBlock {
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> Heap = nullptr;
	int Offset = 0;
	int Capacity = 0;
	UINT DescriptorSize = 0;
	EDescriptorHeapType Type = EDescriptorHeapType::Undefined;
	D3D12_CPU_DESCRIPTOR_HANDLE HeapStartCpu{};
	D3D12_GPU_DESCRIPTOR_HANDLE HeapStartGpu{};

	std::queue<int> RecycleOffset{};

	~DescriptorHeapBlock() = default;

	DescriptorHeapBlock(int InCapacity,EDescriptorHeapType InType, UINT InDescriptorSize)
	{
		Capacity = InCapacity;
		DescriptorSize = InDescriptorSize;
	}

	void CreateHeapRTV(ID3D12Device* InDevice);
	void CreateHeapDSV(ID3D12Device* InDevice);
	void CreateHeapCBVSRVUAV(ID3D12Device* InDevice);

	bool IsFull() const {
		return Offset == Capacity;
	}

	/// <summary>
	/// \brief allocate descriptor in linear, if Recycle queue is not empty, reuse the offset in queue front
	/// </summary>
	/// <param name="InAllocator"></param>
	void Allocate(FHeapAllocator* InAllocator);

	/// <summary>
	/// \brief return the Offset index to Recycle queue, and if the free idx equals the Offset member, decrease Offset only
	/// </summary>
	/// <param name="InAllocator"></param>
	void Free(FHeapAllocator* InAllocator);

	/// <summary>
	/// \brief imgui heap alloc fn version 
	/// \see void Allocate(FHeapAllocator* InAllocator);
	/// </summary>
	/// <param name="out_cpu_desc_handle"></param>
	/// <param name="out_gpu_desc_handle"></param>
	void Allocate(D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_desc_handle);

	/// <summary>
	/// \brief imgui heap alloc fn version
	/// \see void Free(FHeapAllocator* InAllocator);
	/// </summary>
	/// <param name="out_cpu_desc_handle"></param>
	/// <param name="out_gpu_desc_handle"></param>
	void Free(D3D12_CPU_DESCRIPTOR_HANDLE out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE out_gpu_desc_handle);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(int InOffset);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle(int InOffset);
};


/// <summary>
/// \brief lazy singleton,
/// manage heap descriptor
/// 
/// </summary>
class FDescriptorHeapManager
{
	std::unordered_map<std::string , DescriptorHeapBlock> DescriptorHeaps;

	UINT RtvDescriptorSize = 0;
	UINT DsvDescriptorSize = 0;
	UINT CbvSrvUavDescriptorSize = 0;

	bool IsInitialized = false;

protected:


public:
	explicit FDescriptorHeapManager(ID3D12Device* InDevice) ;

	/// <summary>
	/// return the heap block for specific type
	/// </summary>
	/// <param name="InType"></param>
	/// <returns></returns>
	DescriptorHeapBlock* GetHeapBlock(EDescriptorHeapType InType);

	//TODO add bitmap to track allocated descriptors and support deallocation
	void Allocate(EDescriptorHeapType type, FHeapAllocator* InAllocator);

	/// <summary>
	/// \todo make a bitmap to manage
	/// </summary>
	/// <param name="type"></param>
	/// <param name="InAllocator"></param>
	void Free(EDescriptorHeapType type, FHeapAllocator* InAllocator);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(EDescriptorHeapType type, int InIdx);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle(EDescriptorHeapType type, int InIdx);

	ID3D12DescriptorHeap* GetRawHeap(EDescriptorHeapType InType);

	static void ImGUISrvAllocFn(D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_desc_handle);
	static void ImGUISrvFreeFn(D3D12_CPU_DESCRIPTOR_HANDLE out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE out_gpu_desc_handle);
};