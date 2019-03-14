#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Device.h"

//2D�e�N�X�`�����N���X
class CTexture2D : public CDeviceUser {
protected:
	ComPtr<ID3D11Texture2D> m_texture;

public:
	virtual ~CTexture2D() {}

	//�o�b�N�o�b�t�@��p
	virtual bool Initialize(ID3D11Texture2D* backBufferPtr) { return false; }

	//���ėp�e�N�X�`��������
	virtual bool Initialize(int width, int height, int mipLevel, D3D11_SUBRESOURCE_DATA* initData = nullptr) { return false; }

	//�ǂݍ��݃e�N�X�`���p�������֐�
	virtual bool Initialize(const char* filename) { return false; }

	ComPtr<ID3D11Texture2D> GetSourcePtr() { return m_texture; }

	virtual ID3D11ShaderResourceView* GetSRV() { return NULL; }
	virtual ID3D11RenderTargetView* GetRTV() { return NULL; }
	virtual ID3D11UnorderedAccessView* GetUAV() { return NULL; }
	virtual ID3D11DepthStencilView* GetDSV() { return NULL; }

	virtual void BeginPass(float r, float g, float b, float a) {}
};


#endif