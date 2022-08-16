#pragma once

#include <Always.h>

#include <d3d11.h>

class CMainDialog
{
public:
    static bool ProcessFrame();

    static void Menu_Handler(bool& done);
    static void Menu_File_Handler(bool& done);
    static void Menu_File_New_Handler(bool& done);
    static void Menu_File_Open_Handler(bool& done);
    static void Menu_File_Save_Handler(bool& done);
    static void Menu_File_SaveAs_Handler(bool& done);
    static void Menu_File_Exit_Handler(bool& done);

    static void Dialog_Handler();
};
