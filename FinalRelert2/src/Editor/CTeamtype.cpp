#include <CTeamtype.h>

#include <imgui.h>

CTeamtype CTeamtype::Instance;

void CTeamtype::Handle()
{
    static bool is_open;
    ImGui::Checkbox("Teamtype", &is_open);
    if (is_open)
    {
        ImGui::Begin("Teamtype", &is_open);

        ImGui::Text("This is the teamtype dialog");

        ImGui::End();
    }
}
