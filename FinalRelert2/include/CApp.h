#pragma once

#include <Always.h>

#include <d3d11.h>

class CApp
{
public:
    static ID3D11Device* g_pd3dDevice;
    static ID3D11DeviceContext* g_pd3dDeviceContext;
    static IDXGISwapChain* g_pSwapChain;
    static ID3D11RenderTargetView* g_mainRenderTargetView;

    static bool Run();
};