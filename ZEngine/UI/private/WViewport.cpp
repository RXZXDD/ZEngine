#include "../public/WViewport.h"
#include "Core/GlobalCore.h"

ZEngine::WViewport::WViewport(const std::string& InName)
{
	Label = InName;
}

ZEngine::WViewport::WViewport(const std::string& InName, const FFloatPoint& InSize, ZEngine::Render::FSceneRenderer* InRenderer)
	: WViewport(InName)
{	
	OnViewportResizeDelegate.BindMember(&ZEngine::Render::FSceneRenderer::UpdateViewportSize, InRenderer);
	UpdateWindowSize(InSize);
}

void ZEngine::WViewport::Tick(const float DeltaTime)
{
	ImGui::Begin("View"
		, nullptr
		, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	 auto NewWindowSize = ImGui::GetWindowSize();

	 UpdateWindowSize(FFloatPoint{ NewWindowSize.x, NewWindowSize.y });

	 ImGui::Image(TextureRef, ImVec2{ WindowSize.X, WindowSize.Y });

	 IsFocused = ImGui::IsWindowFocused();
	 if (IsFocused)
	 {
		 if(LastFrameIsFocused != IsFocused)
		 {
			 ZLOG(Default, Display, "Viewport is focused");
			 LastFramePos = ImGui::GetMousePos();

		 }
		 if (ImGui::GetIO().MouseClicked[0])
		 {

		 }
		 if (ImGui::GetIO().MouseDown[0])
		 {
			 auto NewMousePos = ImGui::GetMousePos();

			 auto DeltaMousePos = ImVec2{ NewMousePos.x - LastFramePos.x
										 ,NewMousePos.y - LastFramePos.y };
			// ZLOG(Default, Display, " Delta Mouse Pos: {}, {}", DeltaMousePos.x, DeltaMousePos.y);
		 }
	 }

	LastFramePos = ImGui::GetMousePos();
	LastFrameIsFocused = IsFocused;
	ImGui::End();

}

void ZEngine::WViewport::UpdateWindowSize(const FFloatPoint& InSize)
{

	if (InSize != FFloatPoint::Zero() && WindowSize != InSize)
	{
		WindowSize = InSize;
		TextureRef._TexID = OnViewportResizeDelegate.ExecuteIfSafe(WindowSize);

	}

}
