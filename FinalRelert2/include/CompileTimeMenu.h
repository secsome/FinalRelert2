#pragma once

#include <Always.h>

#include <imgui.h>

#include <tuple>

// Compile Menu Helper

template<size_t N>
struct StringLiteral
{
    constexpr StringLiteral(const char(&str)[N])
    {
        std::copy_n(str, N, value);
    }

    char value[N];
};

template<StringLiteral Label, StringLiteral ShortCut, void (*Callback)(bool& done)>
struct Menu
{
    static constexpr auto GetLabel()
    {
        return Label.value;
    }

    static constexpr auto GetShortCur()
    {
        return ShortCut.value;
    }

    static constexpr auto GetCallback()
    {
        return Callback;
    }
};

struct MenuSeparator
{
};

template<StringLiteral Label, typename ...Ts>
struct ComposedMenu
{
    static constexpr auto GetLabel()
    {
        return Label.value;
    }

    using TupleType = std::tuple<Ts...>;
};

namespace details
{
    template<StringLiteral Label, StringLiteral ShortCut, void (*Callback)(bool& done)>
    constexpr void ProcessMenuItem(bool& done, Menu<Label, ShortCut, Callback> const& menu)
    {
        if constexpr (ShortCut.value[0] != '\0')
        {
            if (ImGui::MenuItem(Label.value, ShortCut.value))
            {
                if constexpr (Callback != nullptr)
                    Callback(done);
            }
        }
        else
        {
            if (ImGui::MenuItem(Label.value))
            {
                if constexpr (Callback != nullptr)
                    Callback(done);
            }
        }
    }

    static void ProcessMenuItem(bool& done, MenuSeparator const& menu)
    {
        ImGui::Separator();
    }

    template<size_t Index = 0, typename ...Ts>
    constexpr void ProcessMenuItemsHelper(bool& done, std::tuple<Ts...> const& menus)
    {
        if constexpr (Index != sizeof ...(Ts))
        {
            ProcessMenuItem(done, std::get<Index>(menus));
            ProcessMenuItemsHelper<Index + 1>(done, menus);
        }
    }

    template<typename ...Ts>
    constexpr void ProcessMenuItems(bool& done, std::tuple<Ts...> const& menus)
    {
        ProcessMenuItemsHelper(done, menus);
    }

    template<typename ComposedMenuType>
    constexpr void ProcessComposeMenu(bool& done)
    {
        using UnRefComposedMenuType = std::remove_reference_t<ComposedMenuType>;
        if (ImGui::BeginMenu(UnRefComposedMenuType::GetLabel()))
        {
            ProcessMenuItems(done, UnRefComposedMenuType::TupleType());
            ImGui::EndMenu();
        }
    }

    template<size_t Index = 0, typename ...Ts>
    constexpr void ProcessTupleMenuHelper(bool& done, std::tuple<Ts...> const& menus)
    {
        if constexpr (Index != sizeof ...(Ts))
        {
            ProcessComposeMenu<decltype(std::get<Index>(menus))>(done);
            ProcessTupleMenuHelper<Index + 1>(done, menus);
        }
    }

    template<typename ...Ts>
    constexpr void ProcessTupleMenu(bool& done, std::tuple<Ts...> const& menus)
    {
        if (ImGui::BeginMenuBar())
        {
            ProcessTupleMenuHelper(done, menus);
            ImGui::EndMenuBar();
        }
    }
}

template<typename T>
constexpr void ProcessMenus(bool& done)
{
    details::ProcessTupleMenu(done, T{});
}