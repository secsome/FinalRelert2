#include <CTaskforce.h>

#include <imgui.h>

void CTaskforce::Handle()
{
    static bool is_open;
    ImGui::Checkbox("Taskforce", &is_open);
    if (is_open)
    {
        ImGui::Begin("Taskforce", &is_open);

        ImGui::Text("This is the taskforce dialog");

        ImGui::End();
    }
}
