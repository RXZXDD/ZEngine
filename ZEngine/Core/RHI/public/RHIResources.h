#pragma once
#include "RHIDefinitions.h"
#include "Core/Misc/public/PixelFormat.h"
#include "Core/Misc/public/CombineType.h"

#include <string>
#include <cassert>
#include <memory>



namespace ZEngine::RHI
{
	/// <summary>
	/// @brief base type of RHI resource
	/// </summary>
	class FRHIResource
	{
		ERHIResourceType Type = RRType_None;
	public:
		FRHIResource() = default;
		FRHIResource(ERHIResourceType InType) : Type(InType) {}
		ERHIResourceType GetType() const { return Type; }

	protected:
		virtual ~FRHIResource();

	};

	class FRHIViewableResource: public FRHIResource
	{
		protected:
			std::string Name;
	public:
		FRHIViewableResource() = default;
	};

	enum class EClearBinding
	{
		ENoneBound, //no clear color associated with this target.  Target will not do hardware clears on most platforms
		EColorBound, //target has a clear color bound.  Clears will use the bound color, and do hardware clears.
		EDepthStencilBound, //target has a depthstencil value bound.  Clears will use the bound values and do hardware clears.
	};

	/// <summary>
	/// @todo duel with color space
	/// </summary>
	struct FClearValueBinding
	{
		struct DSVAlue
		{
			float Depth;
			uint32 Stencil;
		};

		union ClearValueType
		{
			float Color[4];
			DSVAlue DSValue;
		} Value;

		FClearValueBinding()
			: ColorBinding(EClearBinding::EColorBound)
		{
			Value.Color[0] = 0.0f;
			Value.Color[1] = 0.0f;
			Value.Color[2] = 0.0f;
			Value.Color[3] = 0.0f;
		}

		explicit FClearValueBinding(float DepthClearValue, uint32 StencilClearValue = 0)
			: ColorBinding(EClearBinding::EDepthStencilBound)
		{
			Value.DSValue.Depth = DepthClearValue;
			Value.DSValue.Stencil = StencilClearValue;
		}

		void GetDepthStencil(float& OutDepth, uint32& OutStencil) const
		{
			assert(ColorBinding == EClearBinding::EDepthStencilBound);
			OutDepth = Value.DSValue.Depth;
			OutStencil = Value.DSValue.Stencil;
		}

		EClearBinding ColorBinding;
	};

	/// <summary>
	/// @brief A Desc use for create texture
	/// </summary>
	struct FRHITextureDesc 
	{
		FRHITextureDesc() = default;
		FRHITextureDesc(const FRHITextureDesc& rhs)
		{
		}

		FRHITextureDesc(
			ETextureDimension   InDimension
			, ETextureCreateFlags InFlags
			, EPixelFormat        InFormat
			, FClearValueBinding  InClearValue
			, FIntPoint           InExtent
			, uint16              InDepth
			, uint16              InArraySize
			, uint8               InNumMips
			, uint8               InNumSamples
			, uint32              InExtData
		) : Flags(InFlags)
			, ClearValue(InClearValue)
			, ExtData(InExtData)
			, Extent(InExtent)
			, Depth(InDepth)
			, ArraySize(InArraySize)
			, NumMips(InNumMips)
			, NumSamples(InNumSamples)
			, Dimension(InDimension)
			, Format(InFormat)
		{}

		void Reset()
		{
			// Usually we don't want to propagate MSAA samples.
			NumSamples = 1;

			// Remove UAV flag for textures that don't need it (some formats are incompatible).
			Flags |= TexCreate_RenderTargetable;
			Flags &= ~(TexCreate_UAV | TexCreate_ResolveTargetable | TexCreate_DepthStencilResolveTarget);

		}

		FIntVector GetSize() const
		{
			return FIntVector(Extent.X, Extent.Y, Depth);
		}

		/** Texture flags passed on to RHI texture. */
		ETextureCreateFlags Flags = TexCreate_None;

		/** Clear value to use when fast-clearing the texture. */
		FClearValueBinding ClearValue;

		/** Platform-specific additional data. Used for offline processed textures on some platforms. */
		uint32 ExtData = 0;

		/** Extent of the texture in x and y. */
		FIntPoint Extent = FIntPoint(1, 1);

		/** Depth of the texture if the dimension is 3D. */
		uint16 Depth = 1;

		/** The number of array elements in the texture. (Keep at 1 if dimension is 3D). */
		uint16 ArraySize = 1;

		/** Number of mips in the texture mip-map chain. */
		uint8 NumMips = 1;

		/** Number of samples in the texture. >1 for MSAA. */
		uint8 NumSamples = 1;

		/** Texture dimension to use when creating the RHI texture. */
		ETextureDimension Dimension = ETextureDimension::Texture2D;

		/** Pixel format used to create RHI texture. */
		EPixelFormat Format = PF_Unknown;

		/** Texture format used when creating the UAV. PF_Unknown means to use the default one (same as Format). */
		EPixelFormat UAVFormat = PF_Unknown;


	};

	class FRHITexture : public FRHIViewableResource
	{
	protected:
		FRHITextureDesc TextureDesc;

	public:
		FRHITexture() = default;

		virtual const FRHITextureDesc& GetDesc() const { return TextureDesc; }

		///
		/// Virtual functions implemented per RHI
		/// 
		
		/// <summary>
		/// @return platform-specific resource pointer
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeResource() const
		{
			return nullptr;
		}

		/// <summary>
		/// @return platform-specific SRV pointer
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeShaderResourceView() const
		{
			return nullptr;
		}

		/// <summary>
		/// @return platform-specific Texture baseclass
		/// </summary>
		/// <returns></returns>
		virtual void* GetTextureBaseRHI()
		{
			// Override this in derived classes to expose access to the native texture resource
			return nullptr;
		}

		float GetDepthClearValue() const
		{
			float Depth;
			uint32 Stencil;
			GetDesc().ClearValue.GetDepthStencil(Depth, Stencil);
			return Depth;
		}

		uint32 GetStencilClearValue() const
		{
			float Depth;
			uint32 Stencil;
			GetDesc().ClearValue.GetDepthStencil(Depth, Stencil);
			return Stencil;
		}

		inline FRHITexture* GetTexture2D() { return TextureDesc.Dimension == ETextureDimension::Texture2D ? this : nullptr; }

	};

	using FRHITextureRef = std::shared_ptr<FRHITexture>;

	class  FRHIGPUFence : public FRHIResource 
	{
		public: 
			FRHIGPUFence(std::string InName)
				: FRHIResource(RRType_GPUFence)
				, FenceName(InName)
			{ }

			std::string_view GetName() const { return FenceName; }
		protected:
			const std::string FenceName;
	};

	//class FRHIDevice : public FRHIResource
	//{
	//public:
	//	virtual void* GetNativeDevice() const
	//	{
	//		return nullptr;
	//	}
	//};


	class FRHIViewport : public FRHIResource
	{
	protected:
		float TopLeftX = 0.f;
		float TopLeftY = 0.f;
		float Width = 0.f;
		float Height = 0.f;
		float MinDepth = 0.f;
		float MaxDepth = 0.f;
	public:
		FRHIViewport() = default;


		virtual void* GetNativeViewport() const
		{
			return nullptr;
		}
	};

	class FRHIMeshData
	{
	public:

		/*UINT IndexCount = 0;
		UINT StartIndexLocation = 0;
		UINT BaseVertexLocation = 0;*/

		virtual void* GetNativeMeshData()
		{
			return nullptr;
		}
	};

	using FRHIMeshDataRef = std::shared_ptr<FRHIMeshData>;

}
