#ifndef _BACKBUFFER_H_
#define _BACKBUFFER_H_

#include "Texture.h"

//バックバッファクラス
class CBackBuffer : CTexture2D {
private:
	ComPtr<ID3D11RenderTargetView> m_rtv;
	ComPtr<ID3D11UnorderedAccessView> m_uav;

public:
	bool Initialize(ID3D11Texture2D* backBufferPtr);

	ID3D11RenderTargetView* GetRTV() { return m_rtv.Get(); }
	ID3D11UnorderedAccessView* GetUAV() { return m_uav.Get(); }

	void BeginPass(float r, float g, float b, float a);
};

#endif