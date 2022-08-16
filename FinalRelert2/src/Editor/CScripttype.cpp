#include <CScripttype.h>

#include <imgui.h>

void CScripttype::Handle()
{
    static bool is_open;
    ImGui::Checkbox("Scripttype", &is_open);
    if (is_open)
    {
        ImGui::Begin("Scripttype", &is_open);

        ImGui::Text("This is the scripttype dialog");

        ImGui::End();
    }
}
