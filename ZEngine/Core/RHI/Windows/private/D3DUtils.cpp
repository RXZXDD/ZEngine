#include "../public/D3DUtils.h"
#include <comdef.h>
#include <fstream>

#include <RHI/Windows/public/D3D12Blob.h>





using Microsoft::WRL::ComPtr;

DxException::DxException(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber) :
    ErrorCode(hr),
    FunctionName(functionName),
    Filename(filename),
    LineNumber(lineNumber)
{
}


std::wstring DxException::ToString() const
{
    // Get the string description of the error code.
    _com_error err(ErrorCode);
    std::wstring msg = err.ErrorMessage();

    return FunctionName + L" failed in " + Filename + L"; line " + std::to_wstring(LineNumber) + L"; error: " + msg;
}

D3D12_COMMAND_LIST_TYPE D3DUtils::GetD3DCommandListType(ECommandListType InType)
{
    switch (InType)
    {
    case ECommandListType::DIRECT:
        return D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
    case ECommandListType::UNKNOWN:

    default:
        assert(false && "unknown command list type");
        break;
    }

    return D3D12_COMMAND_LIST_TYPE();
}

D3D12_HEAP_TYPE D3DUtils::GetD3DHeapType(EHeapType InType)
{
	switch (InType)
	{
	case EHeapType::DEFAULT:
		return  D3D12_HEAP_TYPE_DEFAULT;
	case EHeapType::UPLOAD:
		return D3D12_HEAP_TYPE_UPLOAD;

	case EHeapType::COUNT:
	default:
		break;
	}
	return D3D12_HEAP_TYPE();
}

ZEngine::RHI::FD3D12BlobRef D3DUtils::CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target)
{
    UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = S_OK;

    ZEngine::RHI::FD3D12BlobRef byteCode = std::make_shared<ZEngine::RHI::FD3D12Blob>();
    ComPtr<ID3DBlob> errors;

    hr = D3DCompileFromFile(
        filename.c_str(),
        defines,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        entrypoint.c_str(),
        target.c_str(),
        compileFlags,
        0,
        byteCode->GetAddressOf(),
        &errors
	);
    if(errors != nullptr)
    {
        std::string test = static_cast<const char*>(errors->GetBufferPointer());
        std::wstring errorMsg = L"Error compiling shader: " + filename + L"\n";
                                
        OutputDebugStringW(errorMsg.c_str());
		OutputDebugStringA(test.c_str());
	}

    return byteCode;
}

void D3DUtils::CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData, UINT64 byteSize, ZEngine::RHI::FD3D12BufferRef TargetBuffer, ZEngine::RHI::FD3D12BufferRef InUploadBuffer)
{

    TargetBuffer->SetFormat(InUploadBuffer->GetFormat());
	TargetBuffer->SetDesc(InUploadBuffer->GetDesc());

		// Create the actual default buffer resource.
	auto heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(TargetBuffer->GetSize());

		ThrowIfFailed(device->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_COMMON,
			nullptr,
			IID_PPV_ARGS(TargetBuffer->GetAddressOf())));

	// In order to copy CPU memory data into our default buffer, we need to create
	// an intermediate upload heap. 
	auto uploadHeapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto uploadResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(InUploadBuffer->GetSize());

	ThrowIfFailed(device->CreateCommittedResource(
		&uploadHeapProps,
		D3D12_HEAP_FLAG_NONE,
		&uploadResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(InUploadBuffer->GetAddressOf())));

	// Describe the data we want to copy into the default buffer.
	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = TargetBuffer->GetSize();
	subResourceData.SlicePitch = subResourceData.RowPitch;

	// Schedule to copy the data to the default buffer resource.  At a high level, the helper function UpdateSubresources
	// will copy the CPU memory into the intermediate upload heap.  Then, using ID3D12CommandList::CopySubresourceRegion,
	// the intermediate upload heap data will be copied to mBuffer.

	auto barrier1 = CD3DX12_RESOURCE_BARRIER::Transition(TargetBuffer->Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);

	cmdList->ResourceBarrier(1, &barrier1);
	UpdateSubresources<1>(cmdList, TargetBuffer->Get(), InUploadBuffer->Get(), 0, 0, 1, &subResourceData);

	auto barrier2 = CD3DX12_RESOURCE_BARRIER::Transition(TargetBuffer->Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

	cmdList->ResourceBarrier(1, &barrier2);
}
