#pragma once
#include <memory>

#include <Misc/public/PlatformTypeDef.h>
#include "Core/Helper/public/ClassHelper.h"

#include "RHIDefinitions.h"

namespace ZEngine::RHI
{
	/// <summary>
	/// todo: move to toolset.
	/// </summary>
	/// <param name="byteSize"></param>
	/// <returns></returns>
	static uint32 CalcConstantBufferByteSize(uint32 byteSize)
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

	/// <summary>
	/// a buffer description struct.
	/// </summary>
	struct BufferDesc
	{
		bool IsConstant = false;
		size_t ElementSize = 0;
		uint32 ElementCount = 0;
	};

	/// <summary>
	/// a RHI Buffer class, which is the base class of all buffer types, such as vertex buffer, index buffer, constant buffer, etc.
	/// </summary>
	class FRHIBuffer
	{
		BufferDesc Desc;


	public:

		CTR_CP_DEL(FRHIBuffer);
		OP_ASSIGN_CP_DEL(FRHIBuffer);

		FRHIBuffer() = default;

		FRHIBuffer(size_t elementSize, uint32 elementCount, bool isConstant = false);

		virtual ~FRHIBuffer() = default;
		bool IsConstantBuffer() const { return Desc.IsConstant; }

		size_t GetElementSize() const { return Desc.ElementSize; }
		uint32 GetElementCount() const { return Desc.ElementCount; }

		/// <summary>
		/// Get the total size of the buffer in bytes.
		/// </summary>
		/// <returns>The size of the buffer in bytes.</returns>
		size_t GetSize() const { return Desc.ElementSize * Desc.ElementCount; }

		BufferDesc GetDesc() const { return Desc; }

		virtual void* GetNative()
		{
			return nullptr;
		}

		void SetDesc(const BufferDesc& InDesc) { Desc = InDesc; }
	};

	using FRHIBufferRef = std::shared_ptr<FRHIBuffer>;

}
