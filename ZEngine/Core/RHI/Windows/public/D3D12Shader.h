#pragma once

#include <vector>

#include "Render/public/Shader/Shader.h"

#include "RHI/Windows/public/D3D12Blob.h"

namespace ZEngine::Render
{

	/// <summary>
	/// base class of shader use D3D12
	/// </summary>
	class FD3D12Shader : public FShader
	{
	protected:
		RHI::FD3D12BlobRef CodeBlob = nullptr;

		std::vector<D3D12_INPUT_ELEMENT_DESC> InputLayout;


	public:
		virtual ~FD3D12Shader() = default;

		virtual std::string GetName()const override;

		virtual std::string GetFilePath() override;

		virtual void Compile() override;

		virtual std::vector<D3D12_INPUT_ELEMENT_DESC>& GetInputLayout();

		/// <summary>
		/// override to specify shader frquency
		/// </summary>
		/// <returns></returns>
		virtual EFrequency GetFrquency() const;
		virtual std::string GetFrquencyStr() const override;

		std::string GetTargetFeature();

		/// <summary>
		/// override to specify feature level of this shader
		/// default is 11_0
		/// </summary>
		/// <returns></returns>
		virtual D3D_FEATURE_LEVEL GetFeatureSupport() const;
		std::string GetFeatureLevelStr() const;

		std::vector<D3D_SHADER_MACRO> GetD3DDefines();

		void* GetCodeBufferPointer();

		SIZE_T GetCodeBufferSize();
	};

	/// <summary>
	/// default VS, feature = 11_0
	/// </summary>
	class FD3D12VertexShader : public FD3D12Shader
	{
	public:
		virtual EFrequency GetFrquency() const
		{
			return EFrequency::VS;
		}

		virtual D3D_FEATURE_LEVEL GetFeatureSupport() const
		{
			return D3D_FEATURE_LEVEL_11_0;
		}

		virtual std::string GetEntryPoint()
		{
			return "VS";
		}

	};

	/// <summary>
/// default PS, feature = 11_0
/// </summary>
	class FD3D12PixelShader : public FD3D12Shader
	{
	public:
		virtual EFrequency GetFrquency() const
		{
			return EFrequency::PS;
		}

		virtual D3D_FEATURE_LEVEL GetFeatureSupport() const
		{
			return D3D_FEATURE_LEVEL_11_0;
		}

		virtual std::string GetEntryPoint()
		{
			return "PS";
		}

	};


	class FCanvasVS : public FD3D12VertexShader
	{
	public:
		virtual std::string GetName()const
		{
			return "CanvasVS";
		}

		virtual std::string GetFilePath()
		{
			return "./ShaderFile/CanvasVS.hlsl";
		}

		virtual std::vector<D3D12_INPUT_ELEMENT_DESC>& GetInputLayout()
		{
			InputLayout = {

				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			};
			return InputLayout;
		}
	};

	class FCanvasPS : public FD3D12PixelShader
	{
	public:
		virtual std::string GetName()const
		{
			return "CanvasPS";
		}

		virtual std::string GetFilePath()
		{
			return "./ShaderFile/CanvasVS.hlsl";
		}
	};
}
