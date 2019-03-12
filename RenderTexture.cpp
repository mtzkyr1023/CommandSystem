#include "RenderTexture.h"

bool CColorTexture::Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData) {
	HRESULT res;

	D3D11_TEXTURE2D_DESC texDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));

	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = mipLevel;
	texDesc.ArraySize = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	
	res = m_device->CreateTexture2D(&texDesc, initData, m_texture.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating color texture.", "Rendertexture.cpp", MB_OK);
		return false;
	}

	srvDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	res = m_device->CreateShaderResourceView(m_texture.Get(), &srvDesc, m_srv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating color srv.", "RenderTexture.cpp", MB_OK);
		return false;
	}

	rtvDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	res = m_device->CreateRenderTargetView(m_texture.Get(), &rtvDesc, m_rtv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating color rtv.", "RenderTexture.cpp", MB_OK);
		return false;
	}

	return true;
}


bool CNormalTexture::Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData) {
	HRESULT res;

	D3D11_TEXTURE2D_DESC texDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));

	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = mipLevel;
	texDesc.ArraySize = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	res = m_device->CreateTexture2D(&texDesc, initData, m_texture.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating normal texture.", "Rendertexture.cpp", MB_OK);
		return false;
	}

	srvDesc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	res = m_device->CreateShaderResourceView(m_texture.Get(), &srvDesc, m_srv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating noraml srv.", "RenderTexture.cpp", MB_OK);
		return false;
	}

	rtvDesc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	res = m_device->CreateRenderTargetView(m_texture.Get(), &rtvDesc, m_rtv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating normal rtv.", "RenderTexture.cpp", MB_OK);
		return false;
	}

	return true;
}

bool CDepthStencilTexture::Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData) {
	HRESULT res;

	D3D11_TEXTURE2D_DESC texDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));

	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = mipLevel;
	texDesc.ArraySize = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	res = m_device->CreateTexture2D(&texDesc, initData, m_texture.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating depth stencil texture.", "Rendertexture.cpp", MB_OK);
		return false;
	}

	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	res = m_device->CreateDepthStencilView(m_texture.Get(), &dsvDesc, m_dsv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating dsv.", "RenderTexture.cpp", MB_OK);
		return false;
	}

	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	res = m_device->CreateShaderResourceView(m_texture.Get(), &srvDesc, m_dsrv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating dsrv.", "RenderTexture.cpp", MB_OK);
		return false;
	}

	srvDesc.Format = DXGI_FORMAT_X24_TYPELESS_G8_UINT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	res = m_device->CreateShaderResourceView(m_texture.Get(), &srvDesc, m_ssrv.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating ssrv.", "RenderTexture.cpp", MB_OK);
		return false;
	}

	return true;
}