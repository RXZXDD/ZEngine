#pragma once

#include <functional>

#include "WidgetBase.h"
#include <Misc/public/CombineType.h>

#include "Core/Delegate/DelegateMacro.h"

#include "Render/public/SceneRenderer.h"

#include "imgui.h"

DECLEAR_DELEGATE_ONE_PARAM_WITH_RETURN(FOnViewportResize, uint64, const FFloatPoint&);

struct ImTextureRef;

namespace ZEngine
{
	class WViewport : public WWidgetBase
	{
		ImTextureRef TextureRef;

		FFloatPoint WindowSize;
		FOnViewportResize OnViewportResizeDelegate;


	public:
		WViewport(const std::string& InName);

		WViewport(const std::string& InName, const FFloatPoint& InSize, ZEngine::Render::FSceneRenderer* InRenderer);
		virtual ~WViewport() = default;


		// 通过 WWidgetBase 继承
		void Tick(const float DeltaTime) override;

		void UpdateWindowSize(const FFloatPoint& InSize);
	};
}
