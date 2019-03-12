#include "ModelShader.h"

#include "shader/static_model_vs.h"
#include "shader/model_ps.h"

bool CStaticModelVertexShader::Initialize() {
	HRESULT res;

	res = m_device->CreateVertexShader(g_static_vs_main, sizeof(g_static_vs_main), NULL, m_vertexShader.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating static vs.", "ModelShader.cpp", MB_OK);
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	res = m_device->CreateInputLayout(layout, ARRAYSIZE(layout), g_static_vs_main, sizeof(g_static_vs_main), m_layout.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating static layout.", "ModelShader.cpp", MB_OK);
		return false;
	}

	return true;
}

bool CModelPixelShader::Initialize() {
	HRESULT res;

	res = m_device->CreatePixelShader(g_model_ps_main, sizeof(g_model_ps_main), NULL, m_pixelShader.ReleaseAndGetAddressOf());
	if (FAILED(res)) {
		MessageBox(NULL, "failed creating model ps.", "ModelShader.cpp", MB_OK);
		return false;
	}

	return true;
}