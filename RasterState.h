#ifndef _RASTERSTATE_H_
#define _RASTERSTATE_H_

#include "Device.h"

class CRasterState : public CDeviceUser {
private:
	ComPtr<ID3D11RasterizerState> m_rasterState;

public:
	bool Initialize() {
		D3D11_RASTERIZER_DESC rasterDesc;
		ZeroMemory(&rasterDesc, sizeof(rasterDesc));
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		m_device->CreateRasterizerState(&rasterDesc, m_rasterState.ReleaseAndGetAddressOf());

		return true;
	}

	void Set() {
		m_context->RSSetState(m_rasterState.Get());
	}
};

class CViewPort : public CDeviceUser {
private:
	D3D11_VIEWPORT m_viewport;

public:
	bool Initialize(int width, int height) {
		m_viewport.Width = (float)width;
		m_viewport.Height = (float)height;
		m_viewport.MaxDepth = 1.0f;
		m_viewport.MinDepth = 0.0f;
		m_viewport.TopLeftX = 0.0f;
		m_viewport.TopLeftY = 0.0f;

		return true;
	}

	void Set() {
		m_context->RSSetViewports(1, &m_viewport);
	}
};

#endif