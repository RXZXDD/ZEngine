#include "../public/WViewport.h"

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
