#ifndef _SWAPCHAIN_H_
#define _SWAPCHAIN_H_

#include "Device.h"

class CSwapChain : public CDeviceUser {
private:
	ComPtr<IDXGISwapChain> m_swapChain;
	bool m_isVsync;

public:
	CSwapChain() {}
	~CSwapChain() {}

	//�X���b�v�`�F�C��������
	bool Initialize(HWND hwnd, int width, int height, int msaaCount, bool vsync);

	//�o�b�N�o�b�t�@���T�C�Y
	void ResizeBuffer(int width, int height);

	ID3D11Texture2D* GetBackBufferPtr();

	void EndPass();
};

#endif