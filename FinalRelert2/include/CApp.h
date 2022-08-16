#pragma once

#include <Always.h>

#include <d3d11.h>

class CApp
{
public:
    explicit CApp();
    virtual ~CApp();

    CLASS_NOCOPY(CApp);
    CLASS_CANMOVE(CApp);

    WNDCLASSEX wc;
    HWND hWnd;
    ID3D11Device* pd3dDevice;
    ID3D11DeviceContext* pd3dDeviceContext;
    IDXGISwapChain* pSwapChain;
    ID3D11RenderTargetView* mainRenderTargetView;

    void Run();

    class CLoading* Loader;

private:
    bool CreateDeviceD3D();
    void CleanupDeviceD3D();
    void CreateRenderTarget();
    void CleanupRenderTarget();

    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

extern CApp* theApp;