#pragma once
#include <string>
#include <wrl.h>

struct ID3D12Device;
struct ID3D12GraphicsCommandList;
struct ID3D12Resource;
struct FInt2;

class ZTexture
{
	std::string Name;
	std::wstring FileName;

	//TODO 抽出至单独的渲染资源类
	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;

	int HeapIndex = -1; // Index into the descriptor heap for SRV

	//TODO 接入选择文件后可开放
	ZTexture() = delete;
protected:
	void CreateResource(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);
	

public:
	ZTexture(const std::string& name, const std::wstring& fileName) : Name(name), FileName(fileName)
	{
	}

	ID3D12Resource* GetResource() const;

	std::string_view GetName() const;

	FInt2 GetSize() const;
};