#include <CScripttype.h>

#include <imgui.h>

CScripttype CScripttype::Instance;

void CScripttype::Handle()
{
    ImGui::Checkbox("Scripttype", &IsDialogOpen);
    if (IsDialogOpen)
    {
        ImGui::Begin("Scripttype", &IsDialogOpen);
        
        if (ImGui::BeginCombo("Scripts", "This is preview"))
        {
            ImGui::EndCombo();
        }

        ImGui::Separator();
        if (ImGui::BeginListBox("Script actions", { 300,600 }))
        {
            ImGui::EndListBox();
        }

        static bool ck;
        ImGui::Checkbox("Insert mode", &ck);
        
        
        ImGui::End();
    }
}
