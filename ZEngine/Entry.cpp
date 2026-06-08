#pragma once
#include "mimalloc.h"
#include "mimalloc/types.h"
#include "mimalloc-stats.h"
#include "mimalloc-new-delete.h"

#include <string>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include "Misc/cpp/imgui_stdlib.h"
#include <d3d12.h>
#include <dxgi1_5.h>
#include <tchar.h>


#include "GlobalCore.h"

#include "Logger/public/LoggerSuppressor.h"
#include "Core/Misc/public/Timer.h"

#include "UI/public/WidgetBase.h"
#include "UI/public/LogTab.h"

#include "RHI/Windows/public/DX12RHI.h"
#include "RHI/Windows/public/D3D12MeshBuilder.h"


#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif
#include <Render/public/Renderer.h>
#include "Render/public/FrameResource.h"

#include <RHI/Windows/public/DX12RHI.h>
#include <Render/public/SceneRenderer.h>
#include <Render/public/Canvas.h>
#include <UI/public/WViewport.h>
#include <GameObject/public/Camera.h>
import glm;

static const int APP_NUM_FRAMES_IN_FLIGHT = 2;

static HWND g_HWnd = nullptr;
extern std::shared_ptr<ZEngine::RHI::IRHI> ZEngine::RHI::GDynamicRHI;
std::vector<std::shared_ptr<ZEngine::WWidgetBase>> UIKeeper;
static FFloatPoint gWindowSize = { 1280, 720 };
std::unique_ptr<Camera> GCamera = nullptr;

static bool                         g_SwapChainOccluded = false;

#pragma region DATA_Window


#pragma endregion

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/// <summary>
/// UI Update loop. calling Tick()
/// </summary>
/// <param name="InDeltaTime"></param>
void UpdateUI(const float InDeltaTime)
{
    for (auto Widget : UIKeeper)
    {
        if (Widget->IsVisible())
			Widget->Tick(InDeltaTime);
    }
}


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    auto* RHI = ZEngine::RHI::GetD3D12DynamicRHI();

    switch (msg)
    {
    case WM_SIZE:
        assert(RHI);
        RHI->ResizeWindow((UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
		GCamera->SetLens(90.0f, (float)LOWORD(lParam), (float)HIWORD(lParam), 0.1f, 1000.0f);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;


    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

const wchar_t WindowTitle[] = L"ZEngine Editor";

std::unique_ptr<ZEngine::Render::FSceneRenderer> GSceneRenderer;
std::unique_ptr<ZEngine::ZTimer> GTimer;

void EngineInit()
{
    int mi_ver = mi_version();
    mi_option_set(mi_option_show_stats, 1);
    mi_option_set(mi_option_verbose, 1);
    mi_option_set(mi_option_show_errors, 1);

    ZEngine::ZLoggerSuppressor::Get()->ApplyConfig();
    ZLOG(Default, Display, "log module inited")
    ZLOG(Default, Display, "中文测试")
    ZLOG(Default, Display, "using mi-malloc {}", mi_version())


    //create timer
    GTimer = std::make_unique<ZEngine::ZTimer>();

	//GSceneRenderer = std::make_unique<ZEngine::Render::FSceneRenderer>();
    //GSceneRenderer->Initialize(GDynamicRHI.get());

}


int main(int, char**) {

    EngineInit();

    // Make process DPI aware and obtain main monitor scale
    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

    // Create application window
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    g_HWnd = ::CreateWindowW(wc.lpszClassName, WindowTitle, WS_OVERLAPPEDWINDOW, 100, 100, (int)(gWindowSize.X * main_scale), (int)(gWindowSize.Y * main_scale), nullptr, nullptr, wc.hInstance, nullptr);


    ZEngine::RHI::GDynamicRHI = std::make_shared<ZEngine::RHI::FDX12RHI>(g_HWnd);
    
    //Create editor viewport
    //todo: replace magic num with viewport struct
    ZEngine::RHI::GDynamicRHI->CreateViewport(0.0f, 0.0f, (gWindowSize.X * main_scale), (gWindowSize.Y * main_scale), 0.0f, 1.0f);

    //todo: replace with renderer's viewport
    ZEngine::RHI::GDynamicRHI->Initialize();
    

	GCamera = std::make_unique<Camera>();
	
    std::unique_ptr<ZEngine::Render::FSceneRenderer> Renderer = std::make_unique<ZEngine::Render::FSceneRenderer>(ZEngine::RHI::GDynamicRHI.get()
		, GCamera.get(), GTimer.get());

    std::shared_ptr<FCanvas> obj = std::make_shared<FCanvas>(Renderer->GetViewport());

    Renderer->AddDrawable(static_cast<ZEngine::Render::IDrawable*>(obj.get()));

     

    auto* D3DDynamicRHI = ZEngine::RHI::GetD3D12DynamicRHI();

    Renderer->BuildProxyResource(D3DDynamicRHI->GetDevice(), D3DDynamicRHI->GetGraphicCommandList());

    D3DDynamicRHI->CreateShaders();
    D3DDynamicRHI->CreateRootSignature();
    D3DDynamicRHI->CreatePipelineState();

    D3DDynamicRHI->CloseCommandList();
    D3DDynamicRHI->ExecuteCommandList();

    // Show the window
    ::ShowWindow(g_HWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(g_HWnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    ImFont* font =  io.Fonts->AddFontFromFileTTF("C:\\WINDOWS\\FONTS\\SIMFANG.TTF");
    io.FontDefault = font;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(g_HWnd);

    ImGui_ImplDX12_InitInfo init_info = {};
    init_info.Device = ZEngine::RHI::GetD3D12DynamicRHI()->GetDevice();
    init_info.CommandQueue = ZEngine::RHI::GetD3D12DynamicRHI()->GetCommandQueue();
    init_info.NumFramesInFlight = APP_NUM_FRAMES_IN_FLIGHT;
    init_info.RTVFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    init_info.DSVFormat = DXGI_FORMAT_UNKNOWN;
    // Allocating SRV descriptors (for textures) is up to the application, so we provide callbacks.
    // (current version of the backend will only allocate one descriptor, future versions will need to allocate more)
    
    init_info.SrvDescriptorHeap = D3DDynamicRHI->GetDescriptorHeapMgr()->GetRawHeap(EDescriptorHeapType::CBV_SRV_UAV);;
    init_info.SrvDescriptorAllocFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_handle)
        { return FDescriptorHeapManager::ImGUISrvAllocFn(out_cpu_handle, out_gpu_handle); };
    init_info.SrvDescriptorFreeFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle, D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle) 
        { return FDescriptorHeapManager::ImGUISrvFreeFn(cpu_handle, gpu_handle); };
    ImGui_ImplDX12_Init(&init_info);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 clear_color1 = ImVec4(1.f, 0.f, 0.f, 1.00f);




    //UI
	UIKeeper.push_back(std::make_shared<ZEngine::WLogTab>("Log"));
	UIKeeper.push_back(std::make_shared<ZEngine::WViewport>("Viewport"
    ,FFloatPoint{1.f,1.f}
    ,Renderer.get()));




    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window screen locked
        //todo: what is g_SwapChainOccluded
        if ((g_SwapChainOccluded && D3DDynamicRHI->GetSwapChain()->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED) || ::IsIconic(g_HWnd))
        {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;
        
        Renderer->Start();

        // Update Phase
        {
            GTimer->Update();

            GCamera->Update(GTimer->GetDeltaTime());
            Renderer->Update(GTimer->GetDeltaTime());

            // Start the Dear ImGui frame
            ImGui_ImplDX12_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::BeginMainMenuBar();
            ImGui::Text("%1f FPS, timer %3fs, timer fps %1f", io.Framerate, GTimer->GetDeltaTime(), 1.0f / GTimer->GetDeltaTime());
            ImGui::EndMainMenuBar();

            ImGui::DockSpaceOverViewport();


            UpdateUI(GTimer->GetDeltaTime());
        }
       
        // Rendering
        ImGui::Render();



        D3DDynamicRHI->FlushCommandQueue();

        const float clear_color_with_alpha1[4] = { clear_color1.x * clear_color1.w, clear_color1.y * clear_color1.w, clear_color1.z * clear_color1.w, clear_color1.w };



        ID3D12GraphicsCommandList* cmdList = D3DDynamicRHI->GetGraphicCommandList();
        ID3D12CommandQueue* cmdQueue = D3DDynamicRHI->GetCommandQueue();
        D3DDynamicRHI->GetCommandAllocator()->Reset();
        cmdList->Reset(D3DDynamicRHI->GetCommandAllocator(), nullptr);


        ////todo: Render Dear ImGui graphics
        

        auto* EditorCanvas = static_cast<ZEngine::RHI::FD3D12Texture*>(Renderer->GetSceneTexture());

        auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
            EditorCanvas->GetResource(),
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
            D3D12_RESOURCE_STATE_RENDER_TARGET
		);
        cmdList->ResourceBarrier(1,
            &barrier);
        

		auto RTDesc = EditorCanvas->GetCpuHandle();
        auto DSDesc = D3DDynamicRHI->GetStencilBuffer()->GetView();
        cmdList->OMSetRenderTargets(1
            , &RTDesc
            , FALSE
            , &DSDesc);
        cmdList->ClearRenderTargetView(EditorCanvas->GetCpuHandle(), EditorCanvas->GetClearColor().data(), 0, nullptr);

        cmdList->ClearDepthStencilView(D3DDynamicRHI->GetStencilBuffer()->GetView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

		cmdList->RSSetViewports(1
            , D3DDynamicRHI->GetSceneViewport()->GetViewport());


        auto ScissorRect = D3DDynamicRHI->GetSceneViewport()->GetRect();
		cmdList->RSSetScissorRects(1
            , &ScissorRect);

		cmdList->SetPipelineState(D3DDynamicRHI->GetPSO("opaque"));

        std::string rsName = { "Default" };
        cmdList->SetGraphicsRootSignature(D3DDynamicRHI->GetRootSignature(rsName));

        auto* CurFrameResource = Renderer->GetCurrentFrameResource();
        auto MainPassD3DCB = static_cast<ZEngine::RHI::FD3D12Buffer*>(CurFrameResource->GetMainPassCB().get());
        cmdList->SetGraphicsRootConstantBufferView(1, MainPassD3DCB->GetGPUVirtualAddress());
        Renderer->Draw(cmdList);

        auto barrier66 = CD3DX12_RESOURCE_BARRIER::Transition(
            EditorCanvas->GetResource(),
            D3D12_RESOURCE_STATE_RENDER_TARGET,
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
        );
        cmdList->ResourceBarrier(1, &barrier66);

        ////////////////////imgui draw
        {
            auto barrier2 = CD3DX12_RESOURCE_BARRIER::Transition(
                D3DDynamicRHI->GetCurrentBackBuffer()->GetResource(),
                D3D12_RESOURCE_STATE_PRESENT,
                D3D12_RESOURCE_STATE_RENDER_TARGET
            );
            cmdList->ResourceBarrier(1,
                &barrier2);

            auto CurrentBackBufferView = D3DDynamicRHI->GetCurrentBackBuffer()->GetView();
            cmdList->OMSetRenderTargets(1
                , &CurrentBackBufferView
                , FALSE
                , nullptr);

            cmdList->ClearRenderTargetView(D3DDynamicRHI->GetCurrentBackBuffer()->GetView(), clear_color_with_alpha1, 0, nullptr);
            auto* usingSrvHeap = D3DDynamicRHI->GetDescriptorHeapMgr()->GetRawHeap(EDescriptorHeapType::CBV_SRV_UAV);
            cmdList->SetDescriptorHeaps(1, &usingSrvHeap);

            ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmdList);

            auto barrier3 = CD3DX12_RESOURCE_BARRIER::Transition(
                D3DDynamicRHI->GetCurrentBackBuffer()->GetResource(),
                D3D12_RESOURCE_STATE_RENDER_TARGET,
                D3D12_RESOURCE_STATE_PRESENT
            );
            cmdList->ResourceBarrier(1,
                &barrier3);
        }

        auto barrier4 = CD3DX12_RESOURCE_BARRIER::Transition(
            EditorCanvas->GetResource(),
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
            D3D12_RESOURCE_STATE_COMMON
        );
        cmdList->ResourceBarrier(1,
            &barrier4);


        cmdList->Close();

        cmdQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&cmdList);

        // Present
        D3DDynamicRHI->Present();   // Present with vsync

        D3DDynamicRHI->FlushCommandQueue();

		Renderer->End();
    }

    D3DDynamicRHI->FlushCommandQueue();

    // Cleanup
    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    ::DestroyWindow(g_HWnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

	//log module cleanup
	//glogModule.reset();

    return 0;
}

