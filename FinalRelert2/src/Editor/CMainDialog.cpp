#include <CMainDialog.h>

#include <CApp.h>

#include <imgui.h>

#include <LanguageManager.h>
#include <CLoading.h>

bool CMainDialog::ProcessFrame()
{
    bool done = false;

    ImGui::Begin("FinalRelert 2 Control Pad", nullptr, 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_MenuBar | 
        ImGuiWindowFlags_NoDocking
    );
    
    Menu_Handler(done);

    Dialog_Handler();

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
        OPENFILENAME ofn = { 0 };

        char buffer[MAX_PATH] = { 0 };
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = NULL;
        ofn.lpstrFilter =
            "RA2 map file (*.ini)\0*.ini;\0"
            "All files\0*.*;\0"
            ;
        ofn.nFilterIndex = 1;
        ofn.lpstrFile = buffer;
        ofn.nMaxFile = sizeof(buffer);
        ofn.lpstrInitialDir = nullptr;
        ofn.lpstrTitle = "";
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
        if (::GetOpenFileName(&ofn))
        {
            if (!theApp->Loader->LoadMap(buffer))
                ::MessageBox(NULL, "Failed to load the map.", "Error", MB_OK);
        }
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

#include <CTrigger.h>
#include <CTag.h>
#include <CTaskforce.h>
#include <CScripttype.h>
#include <CTeamtype.h>

void CMainDialog::Dialog_Handler()
{
    CTrigger::Handle();
    CTag::Handle();
    CTaskforce::Handle();
    CScripttype::Handle();
    CTeamtype::Handle();
}
