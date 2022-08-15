#pragma once

#include <Always.h>

#include <d3d11.h>

#include <CompileTimeMenu.h>

ID3D11ShaderResourceView* LoadTextureFromFile(const char* filename, int& out_width, int& out_height);

class CMainDialog
{
public:
    static bool ProcessFrame();

    static void Menu_File_Exit_Handler(bool& done);

    using MenuTuple = std::tuple <
        ComposedMenu <"File",
            Menu<"New", "CTRL+N", nullptr>,
            Menu<"Open", "CTRL+O", nullptr>,
            Menu<"Save", "CTRL+S", nullptr>,
            Menu<"Save As", "CTRL+SHIFT+S", nullptr>,
            MenuSeparator,
            Menu<"Exit", "", Menu_File_Exit_Handler>
        >,
        ComposedMenu <"Edit",
            Menu<"Undo", "CTRL+Z", nullptr>,
            Menu<"Redo", "CTRL+X", nullptr>,
            MenuSeparator,
            Menu<"Copy", "CTRL+C", nullptr>,
            Menu<"Copy whole map", "", nullptr>,
            Menu<"Paste", "CTRL+V", nullptr>,
            Menu<"Paste centered", "", nullptr>,
            MenuSeparator
        >, 
        ComposedMenu <"Help",
            Menu<"Info", "", nullptr>,
            MenuSeparator
        >
    >;
};
