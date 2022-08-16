#pragma once

#include <Always.h>

#include <d3d11.h>

class CLoading
{
public:
    explicit CLoading();
    virtual ~CLoading();

    CLASS_NOCOPY(CLoading);
    CLASS_NOMOVE(CLoading);

    ID3D11ShaderResourceView* LoadTextureFromFile(const char* filename, int& out_width, int& out_height);

    bool LoadMap(const char* filename);

private:

};