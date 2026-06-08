#pragma once


#include <glm/glm.hpp>

namespace ZEngine::Render
{
	struct PassConstantBuffer
	{
       glm::mat4x4 View = glm::mat4x4{1.f};
       glm::mat4x4 InvView = glm::mat4x4{1.f};
       glm::mat4x4 Proj = glm::mat4x4{1.f};
       glm::mat4x4 InvProj = glm::mat4x4{1.f};
       glm::mat4x4 ViewProj = glm::mat4x4{1.f};
       glm::mat4x4 InvViewProj = glm::mat4x4{1.f};

        glm::vec3 EyePosW = { 0.0f, 0.0f, 0.0f };
        float cbPerObjectPad1 = 0.0f;

        glm::vec2 RenderTargetSize = { 0.0f, 0.0f };
        glm::vec2 InvRenderTargetSize = { 0.0f, 0.0f };

        float NearZ = 0.0f;
        float FarZ = 0.0f;
        float TotalTime = 0.0f;
        float DeltaTime = 0.0f;

        glm::vec4 FogColor = { 0.7f, 0.7f, 0.7f, 1.0f };

        float gFogStart = 5.0f;
        float gFogRange = 50.0f;
        glm::vec2 cbPerObjectPad2;
        glm::vec4 AmbientLight = { 1.0f, 1.0f, 1.0f, 1.0f };

        //Light Lights[MaxLights];
	};

	struct ObjectConstantBuffer
	{
        glm::mat4x4 World = glm::mat4x4{ 1.0f };

		//todo: handle this in material constant buffer
        glm::mat4x4 TexTrans = glm::mat4x4{ 1.0f };
       /* DirectX::XMFLOAT2 DisplacementMapTexelSize = { 1.0f, 1.0f };
        float GridSpatialStep = 1.0f;
        float Pad;
        UINT MaterialIndex = 0;
        UINT Pad0;
        UINT Pad1;
        UINT Pad2;*/
	};
}
