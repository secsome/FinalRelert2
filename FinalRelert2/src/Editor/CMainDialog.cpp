#include <CMainDialog.h>

#include <CApp.h>

#include <imgui.h>

#include <LanguageManager.h>

bool CMainDialog::ProcessFrame()
{
    bool done = false;

    ImGui::Begin("FinalRelert 2(tm) - No map loaded", nullptr, ImGuiWindowFlags_MenuBar);

    Menu_Handler(done);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();

    return done;
}

void CMainDialog::Menu_Handler(bool& done)
{
    if (ImGui::BeginMenuBar())
    {
        Menu_File_Handler(done);

        ImGui::EndMenuBar();
    }
}

void CMainDialog::Menu_File_Handler(bool& done)
{
    if (ImGui::BeginMenu(LanguageManager::Current["CMainDialog_Menu_File"]))
    {
        Menu_File_New_Handler(done);
        ImGui::Separator();
        Menu_File_Open_Handler(done);
        ImGui::Separator();
        Menu_File_Save_Handler(done);
        Menu_File_SaveAs_Handler(done);
        ImGui::Separator();
        Menu_File_Exit_Handler(done);

        ImGui::EndMenu();
    }
}

void CMainDialog::Menu_File_New_Handler(bool& done)
{
    UNREFERENCED_PARAMETER(done);
    if (ImGui::MenuItem(LanguageManager::Current["CMainDialog_Menu_File_New"]))
    {
        // TODO
    }
}

void CMainDialog::Menu_File_Open_Handler(bool& done)
{
    UNREFERENCED_PARAMETER(done);
    if (ImGui::MenuItem(LanguageManager::Current["CMainDialog_Menu_File_Open"]))
    {
        // TODO
    }
}

void CMainDialog::Menu_File_Save_Handler(bool& done)
{
    UNREFERENCED_PARAMETER(done);
    if (ImGui::MenuItem(LanguageManager::Current["CMainDialog_Menu_File_Save"]))
    {
        // TODO
    }
}

void CMainDialog::Menu_File_SaveAs_Handler(bool& done)
{
    UNREFERENCED_PARAMETER(done);
    if (ImGui::MenuItem(LanguageManager::Current["CMainDialog_Menu_File_SaveAs"]))
    {
        // TODO
    }
}

void CMainDialog::Menu_File_Exit_Handler(bool& done)
{
    if (ImGui::MenuItem(LanguageManager::Current["CMainDialog_Menu_File_Exit"]))
    {
        done = true;
    }
}