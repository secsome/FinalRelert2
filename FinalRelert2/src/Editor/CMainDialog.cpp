#include <CMainDialog.h>

#include <CApp.h>

#include <imgui.h>

#include <array>
#include <string_view>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

ID3D11ShaderResourceView* LoadTextureFromFile(const char* filename, int& out_width, int& out_height)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr)
        return nullptr;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = nullptr;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    CApp::g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    if (pTexture == nullptr)
        return nullptr;

    // Create texture view
    ID3D11ShaderResourceView* ret;
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    CApp::g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &ret);
    pTexture->Release();

    out_width = image_width;
    out_height = image_height;
    stbi_image_free(image_data);

    return ret;
};

bool CMainDialog::ProcessFrame()
{
    bool done = false;

    ImGui::Begin("FinalRelert 2(tm) - No map loaded", nullptr, ImGuiWindowFlags_MenuBar);

    ProcessMenus<MenuTuple>(done);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();

    return done;
}

void CMainDialog::Menu_File_Exit_Handler(bool& done)
{
    done = true;
}