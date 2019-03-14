#ifndef _TEXTURECOMMAND_H_
#define _TEXTURECOMMAND_H_

#include "ResourceCommand.h"

#include "BackBuffer.h"
#include "RenderTexture.h"
#include "SwapChain.h"
#include "RasterState.h"
#include "FontTexture.h"

class CCreateBackBuffer : public CResourceCommand {
private:
	int m_width;
	int m_height;
	HWND m_hwnd;
	int m_msaaCount;
	bool m_vsync;

protected:
	bool Internal() {
		bool res;
		std::shared_ptr<CSwapChain> swapChain;
		std::shared_ptr<CBackBuffer> backBuffer;
		std::shared_ptr<CRasterState> rasterState;
		std::shared_ptr<CViewPort> viewport;

		CFactory<CSwapChain>::Instance().Create(0, swapChain);

		CFactory<CBackBuffer>::Instance().Create(0, backBuffer);

		CFactory<CRasterState>::Instance().Create(0, rasterState);

		CFactory<CViewPort>::Instance().Create(0, viewport);

		res = swapChain->Initialize(m_hwnd, m_width, m_height, m_msaaCount, m_vsync);
		if (!res)
			return false;

		ComPtr<ID3D11Texture2D> backBufferPtr = swapChain->GetBackBufferPtr();

		res = backBuffer->Initialize(backBufferPtr.Get());
		if (!res)
			return false;

		rasterState->Initialize();

		viewport->Initialize(m_width, m_height);

		return true;
	}

public:
	CCreateBackBuffer(HWND hwnd, int width, int height, int msaaCount, bool vsync) : m_hwnd(hwnd), m_width(width), m_height(height),
		m_msaaCount(msaaCount), m_vsync(vsync) {}
	~CCreateBackBuffer() {}
};


class CCreateModelPassTexture : public CResourceCommand {
private:
	int m_width;
	int m_height;

protected:
	bool Internal() {
		bool res;

		std::shared_ptr<CColorTexture> colorTexture;
		std::shared_ptr<CNormalTexture> normalTexture;
		std::shared_ptr<CDepthStencilTexture> depthTexture;


		CFactory<CColorTexture>::Instance().Create(0, colorTexture);
		CFactory<CNormalTexture>::Instance().Create(0, normalTexture);
		CFactory<CDepthStencilTexture>::Instance().Create(0, depthTexture);

		res = colorTexture->Initialize(m_width, m_height, 1);
		if (!res)
			return false;

		res = normalTexture->Initialize(m_width, m_height, 1);
		if (!res)
			return false;

		res = depthTexture->Initialize(m_width, m_height, 1);
		if (!res)
			return false;

		return true;
	}

public:
	CCreateModelPassTexture(int width, int height) : m_width(width), m_height(height) {}
};


class CCreateFontTexture : public CResourceCommand {
private:
	std::string m_filename;

protected:
	bool Internal() {
		bool res;

		std::shared_ptr<CFontTexture> font;
		CFactory<CFontTexture>::Instance().Create(0, font);

		res = font->Initialize(m_filename.c_str());
		if (!res)
			return false;

		return true;
	}

public:
	CCreateFontTexture(const char* filename) : m_filename(filename) {}
};


#endif