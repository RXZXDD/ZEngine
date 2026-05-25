#pragma once
#include  "Core/Misc/public/PlatformTypeDef.h"
#include  "Core/Misc/public/EnumClassFlags.h"


enum class ERHIType : uint8
{
	None,
	DX12,
	Unknown
};


enum class EHeapType : uint8
{
	DEFAULT,
	UPLOAD,
	COUNT
};

enum class ECommandListType : uint8
{
	DIRECT,
	UNKNOWN,
	COUNT
};

enum class ERHIResourceType:uint8
{
	RRT_None,
	RRT_Texture,
	RRT_Buffer,
	RRT_GPUFence,
	Count
};
// Compatibility defines
#define RRType_None ERHIResourceType::RRT_None
#define RRType_Texture ERHIResourceType::RRT_Texture
#define RRType_Buffer ERHIResourceType::RRT_Buffer
#define RRType_GPUFence ERHIResourceType::RRT_GPUFence


enum ETextureDimension : uint8
{
	Texture2D,
	Texture2DArray,
	Texture3D,
	TextureCube,
	TextureCubeArray
};

enum class ETextureCreateFlags : uint8
{
	None = 0,

	// Texture can be used as a render target
	RenderTargetable = 1ull << 0,
	// Texture can be used as a resolve target
	ResolveTargetable = 1ull << 1,
	// Texture can be used as a depth-stencil target.
	DepthStencilTargetable = 1ull << 2,
	// Texture can be used as a shader resource.
	ShaderResource = 1ull << 3,

	UAV = 1ull << 4,

	DepthStencilResolveTarget = 1ull << 5
};
ENUM_CLASS_FLAGS(ETextureCreateFlags)

// Compatibility defines
#define TexCreate_None                           ETextureCreateFlags::None
#define TexCreate_RenderTargetable               ETextureCreateFlags::RenderTargetable
#define TexCreate_ResolveTargetable              ETextureCreateFlags::ResolveTargetable
#define TexCreate_DepthStencilTargetable         ETextureCreateFlags::DepthStencilTargetable
#define TexCreate_ShaderResource                 ETextureCreateFlags::ShaderResource
#define TexCreate_UAV                            ETextureCreateFlags::UAV
#define TexCreate_DepthStencilResolveTarget      ETextureCreateFlags::DepthStencilResolveTarget

