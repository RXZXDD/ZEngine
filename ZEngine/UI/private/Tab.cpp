#include "../public/Tab.h"

#include "imgui.h"

#include "mimalloc-stats.h"

#include "GlobalCore.h"

#include <iostream>

namespace ZEngine
{
    static int cnt = 0;

    static void get_mi_output(const char* msg, void* arg) {
        auto pss = static_cast<std::stringstream*>(arg);
        if (pss) {
            *pss << msg;
        }
    };

    WTab::WTab(std::string inLabel)
    {
        _Label = inLabel;
    }

    WTab::~WTab()
    {
    }

    void WTab::Update()
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
            if (auto LogTab = GLog->GetOutputDeviceTab()) {
                LogTab->Clear();
                mi_collect(true);
            }
        }
        if (auto LogTab = GLog->GetOutputDeviceTab()) {
            LogTab->DisplayLogToTab(&ImGui::InputTextMultiline, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_ReadOnly);
        }

		ImGui::End();

        ProcessLogic();
    }

    void WTab::ProcessLogic()
    {

    }

}