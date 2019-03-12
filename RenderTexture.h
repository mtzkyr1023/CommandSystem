#ifndef _RENDERTEXTURE_H_
#define _RENDERTEXTURE_H_

#include "Texture.h"

class CColorTexture : public CTexture2D {
private:
	ComPtr<ID3D11ShaderResourceView> m_srv;
	ComPtr<ID3D11RenderTargetView> m_rtv;

public:
	bool Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData = nullptr);

	ID3D11ShaderResourceView* GetSRV() { return m_srv.Get(); }
	ID3D11RenderTargetView* GetRTV() { return m_rtv.Get(); }
};


class CNormalTexture : public CTexture2D {
private:
	ComPtr<ID3D11ShaderResourceView> m_srv;
	ComPtr<ID3D11RenderTargetView> m_rtv;

public:
	bool Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData = nullptr);

	ID3D11ShaderResourceView* GetSRV() { return m_srv.Get(); }
	ID3D11RenderTargetView* GetRTV() { return m_rtv.Get(); }
};


class CDepthStencilTexture : public CTexture2D {
private:
	ComPtr<ID3D11ShaderResourceView> m_dsrv;
	ComPtr<ID3D11ShaderResourceView> m_ssrv;
	ComPtr<ID3D11DepthStencilView> m_dsv;

public:
	bool Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData = nullptr);

	ID3D11ShaderResourceView* GetDSRV() { return m_dsrv.Get(); }
	ID3D11ShaderResourceView* GetSSRV() { return m_ssrv.Get(); }
	ID3D11DepthStencilView* GetDSV() { return m_dsv.Get(); }
};


#endif