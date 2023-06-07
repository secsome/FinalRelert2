#pragma once

#include <Always.h>

template<typename T>
concept Is2DLocateable = requires(T x)
{
    x.X;
    x.Y;
    x.AsIndex();
};

template<typename T>
concept IsRegistable = requires(T x)
{
    x.RegName;
};