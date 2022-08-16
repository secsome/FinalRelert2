#pragma once

#include <Always.h>

#include <d3d11.h>

ID3D11ShaderResourceView* LoadTextureFromFile(const char* filename, int& out_width, int& out_height);

class CMainDialog
{
public:
    static bool ProcessFrame();

    static void Menu_Handler(bool& done);
    static void Menu_File_Handler(bool& done);
    static void Menu_File_Exit_Handler(bool& done);
};
