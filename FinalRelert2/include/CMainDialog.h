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
            Menu<"Exit", "ALT+F4", Menu_File_Exit_Handler>
        >,
        ComposedMenu <"Edit",
            Menu<"Undo", "CTRL+Z", nullptr>,
            Menu<"Redo", "CTRL+X", nullptr>,
            MenuSeparator,
            Menu<"Copy", "CTRL+C", nullptr>,
            Menu<"Copy whole map", "", nullptr>,
            Menu<"Paste", "CTRL+V", nullptr>,
            Menu<"Paste centered", "", nullptr>,
            MenuSeparator,
            Menu<"Map", "", nullptr>,
            Menu<"Basic", "", nullptr>,
            Menu<"SpecialFlags", "", nullptr>,
            Menu<"Lighting", "", nullptr>,
            Menu<"SingleplayerSettings", "", nullptr>,
            MenuSeparator,
            Menu<"Houses", "", nullptr>,
            MenuSeparator,
            Menu<"Trigger", "", nullptr>,
            Menu<"Tag", "", nullptr>,
            MenuSeparator,
            Menu<"Taskforce", "", nullptr>,
            Menu<"Script", "", nullptr>,
            Menu<"Teamtype", "", nullptr>,
            MenuSeparator,
            Menu<"AITrigger", "", nullptr>,
            Menu<"AITriggerEnable", "", nullptr>,
            MenuSeparator,
            Menu<"LocalVariable", "", nullptr>
        >, 
        ComposedMenu <"Tile",
            Menu<"Heighten ground", "", nullptr>,
            Menu<"Lower ground", "", nullptr>,
            Menu<"Make terrain flat", "", nullptr>,
            MenuSeparator,
            Menu<"Hide tileset", "", nullptr>,
            Menu<"Show all tilesets", "", nullptr>,
            Menu<"Hide single field", "", nullptr>,
            Menu<"Show all fields", "", nullptr>,
            MenuSeparator,
            Menu<"Raise single tile", "", nullptr>,
            Menu<"Lower single tile", "", nullptr>
        >,
        ComposedMenu <"Tool",
            Menu<"Change map height", "", nullptr>,
            MenuSeparator,
            Menu<"Auto create shores", "", nullptr>,
            Menu<"Auto cliff flatter", "", nullptr>,
            MenuSeparator,
            Menu<"Paint cliff front", "", nullptr>,
            Menu<"Paint cliff back", "", nullptr>,
            MenuSeparator,
            Menu<"Search waypoint", "", nullptr>,
            MenuSeparator,
            Menu<"Tool scripts", "", nullptr>
        >,
        ComposedMenu <"Option",
            Menu<"Settings", "", nullptr>,
            MenuSeparator,
            Menu<"Show minimap", "", nullptr>,
            MenuSeparator,
            Menu<"Play sound", "", nullptr>,
            Menu<"Show building outline", "", nullptr>,
            Menu<"Disable auto LAT", "", nullptr>
        >,
        ComposedMenu <"Help",
            Menu<"Info", "", nullptr>,
            MenuSeparator
        >
    >;
};
