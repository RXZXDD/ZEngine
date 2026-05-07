#include <iostream>

#include "mimalloc-stats.h"

#include "imgui.h"
#include "Misc/cpp/imgui_stdlib.h"

#include "GlobalCore.h"
#include "../public/LogTab.h"
#include "Logger/public/OutputDeviceTab.h"

#include <sstream>

static int cnt = 0;

static void get_mi_output(const char* msg, void* arg) {
    auto pss = static_cast<std::stringstream*>(arg);
    if (pss) {
        *pss << msg;
    }
};

ZEngine::WLogTab::WLogTab(std::string inLabel) : WTab(inLabel)
{
    LogTab = GLog->GetOutputDeviceTab();
    assert(LogTab && "Failed to get output device tab");

	LogTab->OnNewLog.BindMember(&WLogTab::DisplayLogToTab, this);
}

ZEngine::WLogTab::~WLogTab()
{
    LogTab->OnNewLog.Unbind();
}

void ZEngine::WLogTab::Tick(const float DeltaTime)
{
    ImGui::Begin(_Label.c_str());

    if (ImGui::Button("AddLog"))
    {
        ZLOG(Default, Warning, "add log {}", std::to_string(cnt))
            ++cnt;
    }
    ImGui::SameLine();
    if (ImGui::Button("PrintMemoStat"))
    {
        std::stringstream ss;
        mi_stats_print_out(get_mi_output, (void*)&ss);
        //std::cout << ss.str();
        ZLOG(Default, Display, "\n{}", ss.str());

    }
    ImGui::SameLine();

    if (ImGui::Button("Clear"))
    {
        LogTab->Clear();
		OutputCache.clear();
        mi_collect(true);
    }

    ImGui::InputTextMultiline("##", &OutputCache, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_ReadOnly, nullptr, nullptr);

    ImGui::End();
}

void ZEngine::WLogTab::DisplayLogToTab(const ZLogRecord& NewLog)
{
    OutputCache += NewLog.msg;
}
