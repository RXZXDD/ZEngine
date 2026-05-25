#pragma once

#include "RHI/Windows/public/MathHelper.h"


namespace ZEngine::Render
{
	struct PassConstantBuffer
	{
        DirectX::XMFLOAT4X4 View = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 InvView = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 Proj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 InvProj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 ViewProj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 InvViewProj = MathHelper::Identity4x4();

        DirectX::XMFLOAT3 EyePosW = { 0.0f, 0.0f, 0.0f };
        float cbPerObjectPad1 = 0.0f;

        DirectX::XMFLOAT2 RenderTargetSize = { 0.0f, 0.0f };
        DirectX::XMFLOAT2 InvRenderTargetSize = { 0.0f, 0.0f };

        float NearZ = 0.0f;
        float FarZ = 0.0f;
        float TotalTime = 0.0f;
        float DeltaTime = 0.0f;

        DirectX::XMFLOAT4 FogColor = { 0.7f, 0.7f, 0.7f, 1.0f };

        float gFogStart = 5.0f;
        float gFogRange = 50.0f;
        DirectX::XMFLOAT2 cbPerObjectPad2;

        DirectX::XMFLOAT4 AmbientLight = { 1.0f, 1.0f, 1.0f, 1.0f };

        //Light Lights[MaxLights];
	};

	struct ObjectConstantBuffer
	{
        DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 TexTrans = MathHelper::Identity4x4();
       /* DirectX::XMFLOAT2 DisplacementMapTexelSize = { 1.0f, 1.0f };
        float GridSpatialStep = 1.0f;
        float Pad;
        UINT MaterialIndex = 0;
        UINT Pad0;
        UINT Pad1;
        UINT Pad2;*/
	};
}
