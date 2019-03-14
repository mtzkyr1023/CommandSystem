
#include <vector>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_lib/stb_image.h"

#include "FontTexture.h"

bool CFontTexture::Initialize(const char* filename) {
	HRESULT res;
	int width;
	int height;
	int bpp;
	BYTE* pixel = stbi_load(filename, &width, &height, &bpp, 4);
	DWORD* tmp = new DWORD[width * height];
	for (int i = 0; i < width * height; i++) {
		tmp[i] = (DWORD)(pixel[i * 4 + 0]) | ((DWORD)pixel[i * 4 + 1] << 8) | ((DWORD)pixel[i * 4 + 2] << 16) | ((DWORD)pixel[i * 4 + 3] << 24);
	}

	D3D11_TEXTURE2D_DESC texDesc;
	D3D11_SUBRESOURCE_DATA initData;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	ZeroMemory(&initData, sizeof(initData));
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	initData.pSysMem = tmp;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = 0;

	res = m_device->CreateTexture2D(&texDesc, &initData, m_texture.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating font texture.", "FontTexture.cpp", MB_OK);
		return false;
	}

	stbi_image_free(pixel);
	delete[] tmp;

	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;
	
	res = m_device->CreateShaderResourceView(m_texture.Get(), &srvDesc, m_srv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating font srv.", "FontTexture.cpp", MB_OK);
		return false;
	}

	return true;
}