#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Device.h"

//2Dテクスチャ基底クラス
class CTexture2D : public CDeviceUser {
protected:
	ComPtr<ID3D11Texture2D> m_texture;

public:
	virtual ~CTexture2D() {}

	//バックバッファ専用
	virtual bool Initialize(ID3D11Texture2D* backBufferPtr) { return false; }

	//他汎用テクスチャ初期化
	virtual bool Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData = nullptr) { return false; }

	//読み込みテクスチャ用初期化関数
	virtual bool Initialize(const char* filename) { return false; }

	ComPtr<ID3D11Texture2D> GetSourcePtr() { return m_texture; }

	virtual ID3D11ShaderResourceView* GetSRV() { return NULL; }
	virtual ID3D11RenderTargetView* GetRTV() { return NULL; }
	virtual ID3D11UnorderedAccessView* GetUAV() { return NULL; }
	virtual ID3D11DepthStencilView* GetDSV() { return NULL; }

	virtual void BeginPass(float r, float g, float b, float a) {}
};


#endif