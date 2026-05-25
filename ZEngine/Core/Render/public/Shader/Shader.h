#pragma once
#include <string>

#include "Frequnecy.h"
#include <vector>

namespace ZEngine::Render
{
	/// <summary>
	/// Base class of all shaders
	/// </summary>
	class FShader
	{

	public:
		FShader()

		{
		}

		virtual std::string GetName()const = 0;

		virtual std::string GetFilePath() = 0;

		virtual std::string GetEntryPoint() = 0;

		virtual EFrequency GetFrquency() const = 0;

		virtual std::vector<std::pair<std::string, std::string>> GetDefines() const
		{
			return std::vector<std::pair<std::string, std::string>>();

		};

		/// <summary>
		/// todo: add al compiler class to do this job
		/// </summary>
		virtual void Compile() = 0;

		virtual std::string GetFrquencyStr() const = 0;


	};
}
