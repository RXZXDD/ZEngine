#pragma once

#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include "directx/d3dx12.h"
#include "MathHelper.h"
#include "Render/DDSTextureLoader.h"
#include "Core/Render/public/GeometryGenerator.h"


#include "RHI/Windows/public/D3D12Buffer.h"
#include "D3D12Blob.h"
#include "RHI/public/RHIDefinitions.h"


#pragma comment(lib, "dxguid.lib")

extern const int gNumFrameResources;


inline std::wstring AnsiToWString(const std::string& str)
{
    WCHAR buffer[512];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
    return std::wstring(buffer);
}

class  DxException
{
public:
    DxException() = default;
    DxException(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

    std::wstring ToString()const;

    HRESULT ErrorCode = S_OK;
    std::wstring FunctionName;
    std::wstring Filename;
    int LineNumber = -1;
};

// Defines a subrange of geometry in a MeshGeometry.  This is for when multiple
// geometries are stored in one vertex and index buffer.  It provides the offsets
// and data needed to draw a subset of geometry stores in the vertex and index 
// buffers so that we can implement the technique described by Figure 6.3.
//struct  SubmeshGeometry
//{
//    UINT IndexCount = 0;
//    UINT StartIndexLocation = 0;
//    INT BaseVertexLocation = 0;
//
//    // Bounding box of the geometry defined by this submesh. 
//    // This is used in later chapters of the book.
//    DirectX::BoundingBox Bounds;
//};
//
//
//
//struct Light
//{
//	DirectX::XMFLOAT3 Strength = { 0.5f, 0.5f, 0.5f };
//	float FalloffStart = 1.0f;                          // point/spot light only
//	DirectX::XMFLOAT3 Direction = { 0.0f, -1.0f, 0.0f };// directional/spot light only
//	float FalloffEnd = 10.0f;                           // point/spot light only
//	DirectX::XMFLOAT3 Position = { 0.0f, 0.0f, 0.0f };  // point/spot light only
//	float SpotPower = 64.0f;                            // spot light only
//	DirectX::XMFLOAT3 Color = { 1.0f, 1.0f, 1.0f };  // point/spot light only
//	float pad = 0.0f;
//
//};
//
//#define MaxLights 16
//
//struct MaterialConstants
//{
//	DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
//	DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
//	float Roughness = 0.25f;
//
//	// Used in texture mapping.
//	DirectX::XMFLOAT4X4 MatTransform = MathHelper::Identity4x4();
//};
//
//struct MaterialData
//{
//	DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
//	DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
//	float Roughness = 0.25f;
//
//	// Used in texture mapping.
//	DirectX::XMFLOAT4X4 MatTransform = MathHelper::Identity4x4();
//	UINT DiffuseMapIndex = 0;
//	UINT pad0;
//	UINT pad1;
//	UINT pad2;
//};
//
//// Simple struct to represent a material for our demos.  A production 3D engine
//// would likely create a class hierarchy of Materials.
//struct Material
//{
//	// Unique material name for lookup.
//	std::string Name;
//
//	// Index into constant buffer corresponding to this material.
//	int MatCBIndex = -1;
//
//	// Index into SRV heap for diffuse texture.
//	int DiffuseSrvHeapIndex = -1;
//
//	// Index into SRV heap for normal texture.
//	int NormalSrvHeapIndex = -1;
//
//	// Dirty flag indicating the material has changed and we need to update the constant buffer.
//	// Because we have a material constant buffer for each FrameResource, we have to apply the
//	// update to each FrameResource.  Thus, when we modify a material we should set 
//	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
//	int NumFramesDirty = gNumFrameResources;
//
//	// Material constant buffer data used for shading.
//	DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
//	DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
//	float Roughness = .25f;
//	DirectX::XMFLOAT4X4 MatTransform = MathHelper::Identity4x4();
//};

class  D3DUtils {
public:

	static D3D12_COMMAND_LIST_TYPE GetD3DCommandListType(ECommandListType InType);
	static D3D12_HEAP_TYPE GetD3DHeapType(EHeapType InType);


	//static Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
	//	const std::wstring& filename,
	//	const D3D_SHADER_MACRO* defines,
	//	const std::string& entrypoint,
	//	const std::string& target);

	static ZEngine::RHI::FD3D12BlobRef CompileShader(
		const std::wstring& filename,
		const D3D_SHADER_MACRO* defines,
		const std::string& entrypoint,
		const std::string& target);

	static Microsoft::WRL::ComPtr<ID3D12Resource> CreateDefaultBuffer(
		ID3D12Device* device,
		ID3D12GraphicsCommandList* cmdList,
		const void* initData,
		UINT64 byteSize,
		Microsoft::WRL::ComPtr<ID3D12Resource>& uploadBuffer);

	/// <summary>
	/// create a buffer in default heap and a upload buffer in upload heap. then copy data from upload buffer to target buffer
	/// target buffer resource end with D3D12_RESOURCE_STATE_GENERIC_READ
	/// </summary>
	/// <param name="device"></param>
	/// <param name="cmdList"></param>
	/// <param name="initData"></param>
	/// <param name="byteSize"></param>
	/// <param name="TargetBuffer"></param>
	/// <param name="uploadBuffer"></param>
	static void CreateDefaultBuffer(
		ID3D12Device* device,
		ID3D12GraphicsCommandList* cmdList,
		const void* initData,
		UINT64 byteSize,
		ZEngine::RHI::FD3D12BufferRef TargetBuffer,
		ZEngine::RHI::FD3D12BufferRef InUploadBuffer);

	static UINT CalcConstantBufferByteSize(UINT byteSize)
	{
		// Constant buffers must be a multiple of the minimum hardware
		// allocation size (usually 256 bytes).  So round up to nearest
		// multiple of 256.  We do this by adding 255 and then masking off
		// the lower 2 bytes which store all bits < 256.
		// Example: Suppose byteSize = 300.
		// (300 + 255) & ~255
		// 555 & ~255
		// 0x022B & ~0x00ff
		// 0x022B & 0xff00
		// 0x0200
		// 512
		return (byteSize + 255) & ~255;
	}

};


#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw DxException(hr__, L#x, wfn, __LINE__); } \
}
#endif

#ifndef ReleaseCom
#define ReleaseCom(x) { if(x){ x->Release(); x = 0; } } 
#endif