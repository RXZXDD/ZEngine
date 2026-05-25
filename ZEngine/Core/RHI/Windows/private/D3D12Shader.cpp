#include "../public/D3D12Shader.h"

#include "Core/Helper/public/StringHelper.h"

#include "RHI/Windows/public/D3DUtils.h"

#include "GlobalCore.h"
#include "Logger/public/LoggerMacro.h"


std::string ZEngine::Render::FD3D12Shader::GetName() const
{
	ZLOG(Shader, Fatal, "Shader class name not override yet");

	return std::string();
}

std::string ZEngine::Render::FD3D12Shader::GetFilePath()
{
	ZLOG(Shader, Fatal, "Shader[%s] File path not override yet", GetName())
	return std::string();
}

void ZEngine::Render::FD3D12Shader::Compile()
{
	std::wstring WFilePath;
	StringHelper::StringToWString(GetFilePath(), WFilePath);



	CodeBlob = D3DUtils::CompileShader(WFilePath, GetD3DDefines().data(), GetEntryPoint(), GetTargetFeature());

	assert(CodeBlob);
}

std::vector<D3D12_INPUT_ELEMENT_DESC>& ZEngine::Render::FD3D12Shader::GetInputLayout()
{
	InputLayout = {

		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	return InputLayout;
}

ZEngine::Render::EFrequency ZEngine::Render::FD3D12Shader::GetFrquency() const
{
	return EFrequency::Unknown;
}



std::string ZEngine::Render::FD3D12Shader::GetFrquencyStr() const
{
	switch (GetFrquency())
	{
	case EFrequency::VS:
		return "vs";
	case EFrequency::PS:
		return "ps";
	default:
		ZLOG(Shader, Fatal, "Shader Frquency Not Support");

		break;
	}
	return std::string();
}

std::string ZEngine::Render::FD3D12Shader::GetTargetFeature()
{
	return GetFrquencyStr() + "_" + GetFeatureLevelStr();
}

D3D_FEATURE_LEVEL ZEngine::Render::FD3D12Shader::GetFeatureSupport() const
{
	return D3D_FEATURE_LEVEL_11_0;
}

std::string ZEngine::Render::FD3D12Shader::GetFeatureLevelStr() const
{
	auto Level = GetFeatureSupport();
	switch (Level)
	{
	case D3D_FEATURE_LEVEL_11_0:
	case D3D_FEATURE_LEVEL_12_0:
		return "5_0";
	default:
		ZLOG(Shader, Fatal, "No Level Suport")
		break;
	}
	return std::string();
}



std::vector<D3D_SHADER_MACRO> ZEngine::Render::FD3D12Shader::GetD3DDefines()
{
	std::vector<D3D_SHADER_MACRO> macros;

	auto Defines = GetDefines();
	for (auto def : Defines)
	{
		macros.push_back({ def.first.c_str(), def.second.c_str() });
	}
	macros.push_back({ NULL,NULL });
	return macros;
}

void* ZEngine::Render::FD3D12Shader::GetCodeBufferPointer()
{
	return CodeBlob->GetBufferPointer();
}

SIZE_T ZEngine::Render::FD3D12Shader::GetCodeBufferSize()
{
	return CodeBlob->GetBufferSize();
}
