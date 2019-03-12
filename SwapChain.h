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

	//スワップチェイン初期化
	bool Initialize(HWND hwnd, int width, int height, int msaaCount, bool vsync);

	//バックバッファリサイズ
	void ResizeBuffer(int width, int height);

	ID3D11Texture2D* GetBackBufferPtr();

	void EndPass();
};

#endif