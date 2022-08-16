#include <CLoading.h>

#include <CApp.h>

#include <stb_image.h>

#include <CCFile.h>
#include <INI.h>
#include <CMapData.h>

CLoading::CLoading()
{

}

CLoading::~CLoading()
{

}

ID3D11ShaderResourceView* CLoading::LoadTextureFromFile(const char* filename, int& out_width, int& out_height)
{
    CCFileClass file(filename);
    if (!file.Open())
        return nullptr;

    auto buffer = new unsigned char[file.Size()];
    if (buffer == nullptr)
        return nullptr;

    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory(buffer, file.Size(), &image_width, &image_height, nullptr, 4);
    delete[] buffer;
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
    theApp->pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

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
    theApp->pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &ret);
    pTexture->Release();

    out_width = image_width;
    out_height = image_height;
    stbi_image_free(image_data);

    return ret;
}

bool CLoading::LoadMap(const char* filename)
{
    BufferIOFileClass file(filename);
    if (!file.Open())
        return false;

    auto& ini = Map.MapFile;

    if (!ini.Load(file))
        return false;

    if (!ini.Is_Present("Map", "Theater"))
        return false;



    return true;
}
