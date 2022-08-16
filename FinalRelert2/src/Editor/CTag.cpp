#include <CTag.h>

#include <imgui.h>

void CTag::Handle()
{
    static bool is_open;
    ImGui::Checkbox("Tag", &is_open);
    if (is_open)
    {
        ImGui::Begin("Tag", &is_open);

        ImGui::Text("This is the tag dialog");

        ImGui::End();
    }
}
