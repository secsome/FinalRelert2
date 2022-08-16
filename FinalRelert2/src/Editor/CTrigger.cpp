#include <CTrigger.h>

#include <imgui.h>

void CTrigger::Handle()
{
    static bool is_open;
    ImGui::Checkbox("Trigger", &is_open);
    if (is_open)
    {
        ImGui::Begin("Trigger", &is_open);

        ImGui::Text("This is the trigger dialog");

        ImGui::End();
    }
}
