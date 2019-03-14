#ifndef _GRAPHICCOMMAND_H_
#define _GRAPHICCOMMAND_H_

#include <DirectXMath.h>
using namespace DirectX;

#include "Command.h"
#include "Factory.h"

#include "BackBuffer.h"
#include "RenderTexture.h"
#include "SwapChain.h"
#include "ModelShader.h"
#include "LastShader.h"
#include "ConstBuffer.h"
#include "RasterState.h"
#include "FontTexture.h"
#include "Model.h"

class CGraphicCommand : public CCommand, public CDeviceUser {
protected:
	static CCommandManager* m_manager;

protected:
	CGraphicCommand() {
		m_enableTime = 1;
	}

public:
	virtual ~CGraphicCommand() {}

	static void SetManager(CCommandManager* manager) {
		m_manager = manager;
	}
};

class CModelPass : public CGraphicCommand {
private:
	std::shared_ptr<CColorTexture> m_colorTexture;
	std::shared_ptr<CNormalTexture> m_normalTexture;
	std::shared_ptr<CDepthStencilTexture> m_depthTexture;

	std::shared_ptr<CStaticModelVertexShader> m_static_vs;
	std::shared_ptr<CModelPixelShader> m_model_ps;

	std::shared_ptr<CMatrixBuffer> m_viewBuffer;
	std::shared_ptr<CMatrixBuffer> m_projBuffer;

	std::shared_ptr<XMFLOAT4X4> m_viewMatrix;
	std::shared_ptr<XMFLOAT4X4> m_projMatrix;

	std::shared_ptr<CRasterState> m_rasterState;
	std::shared_ptr<CViewPort> m_viewport;

	std::shared_ptr<CFontTexture> m_tex;

	Model m_model;

protected:
	bool Internal() {
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		XMMATRIX* ptr;

		if (SUCCEEDED(m_context->Map(m_viewBuffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
			ptr = (XMMATRIX*)mappedResource.pData;

			*ptr = XMMatrixTranspose(XMLoadFloat4x4(m_viewMatrix.get()));

			m_context->Unmap(m_viewBuffer->GetBuffer().Get(), 0);
		}

		if (SUCCEEDED(m_context->Map(m_projBuffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
			ptr = (XMMATRIX*)mappedResource.pData;

			*ptr = XMMatrixTranspose(XMLoadFloat4x4(m_projMatrix.get()));

			m_context->Unmap(m_projBuffer->GetBuffer().Get(), 0);
		}

		m_context->VSSetConstantBuffers(0, 1, m_viewBuffer->GetBuffer().GetAddressOf());
		m_context->VSSetConstantBuffers(1, 1, m_projBuffer->GetBuffer().GetAddressOf());

		ID3D11ShaderResourceView* srvArray[] = {
			m_tex->GetSRV(),
		};

		

		ID3D11RenderTargetView* rtvArray[] = {
			m_colorTexture->GetRTV(),
			m_normalTexture->GetRTV(),
		};

		for (UINT i = 0; i < ARRAYSIZE(rtvArray); i++) {
			float color[] = {1.0f, 1.0f, 0.5f, 1.0f};
			m_context->ClearRenderTargetView(rtvArray[i], color);
		}
		m_context->ClearDepthStencilView(m_depthTexture->GetDSV(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		m_context->OMSetRenderTargets(ARRAYSIZE(rtvArray), rtvArray, m_depthTexture->GetDSV());

		m_context->PSSetShaderResources(0, ARRAYSIZE(srvArray), srvArray);

		m_static_vs->Set();
		m_model_ps->Set();

		m_rasterState->Set();
		m_viewport->Set();

		m_model.Draw();

		for (UINT i = 0; i < ARRAYSIZE(rtvArray); i++) {
			rtvArray[i] = NULL;
		}
		for (UINT i = 0; i < ARRAYSIZE(srvArray); i++) {
			srvArray[i] = NULL;
		}

		m_context->OMSetRenderTargets(ARRAYSIZE(rtvArray), rtvArray, NULL);
		m_context->PSSetShaderResources(0, ARRAYSIZE(srvArray), srvArray);

		return 1;
	}

public:
	CModelPass() {
		CFactory<CColorTexture>::Instance().Create(0, m_colorTexture);
		CFactory<CNormalTexture>::Instance().Create(0, m_normalTexture);
		CFactory<CDepthStencilTexture>::Instance().Create(0, m_depthTexture);

		CFactory<CStaticModelVertexShader>::Instance().Create(0, m_static_vs);
		CFactory<CModelPixelShader>::Instance().Create(0, m_model_ps);

		CFactory<CMatrixBuffer>::Instance().Create(0, m_viewBuffer);
		CFactory<CMatrixBuffer>::Instance().Create(1, m_projBuffer);

		CFactory<XMFLOAT4X4>::Instance().Create(0, m_viewMatrix);
		CFactory<XMFLOAT4X4>::Instance().Create(1, m_projMatrix);

		CFactory<CRasterState>::Instance().Create(0, m_rasterState);
		CFactory<CViewPort>::Instance().Create(0, m_viewport);

		CFactory<CFontTexture>::Instance().Create(0, m_tex);

		m_model.Initialize();

		if (m_manager) {
			m_manager->RegistBack(this);
		}
	}
};

class CLastPass : public CGraphicCommand {
private:
	std::shared_ptr<CBackBuffer> m_backBuffer;
	std::shared_ptr<CSwapChain> m_swapChain;

	std::shared_ptr<CLastComputeShader> m_last_cs;

	std::shared_ptr<CColorTexture> m_colorTexture;
	std::shared_ptr<CNormalTexture> m_normalTexture;
	std::shared_ptr<CDepthStencilTexture> m_depthTexture;

protected:
	bool Internal() {
		ID3D11UnorderedAccessView* uavArray[] = {
			m_backBuffer->GetUAV(),
		};

		ID3D11ShaderResourceView* srvArray[] = {
			m_colorTexture->GetSRV(),
		};

		m_context->CSSetShaderResources(0, ARRAYSIZE(srvArray), srvArray);
		m_context->CSSetUnorderedAccessViews(0, ARRAYSIZE(uavArray), uavArray, NULL);

		m_last_cs->Set();


		for (UINT i = 0; i < ARRAYSIZE(uavArray); i++)
			uavArray[i] = NULL;
		for (UINT i = 0; i < ARRAYSIZE(srvArray); i++)
			srvArray[i] = NULL;

		m_context->Dispatch(20, 30, 1);


		m_context->CSSetUnorderedAccessViews(0, ARRAYSIZE(uavArray), uavArray, NULL);

		m_context->CSSetShaderResources(0, ARRAYSIZE(srvArray), srvArray);

		
		m_swapChain->EndPass();


		return 1;
	}

public:
	CLastPass() {
		CFactory<CBackBuffer>::Instance().Create(0, m_backBuffer);
		CFactory<CSwapChain>::Instance().Create(0, m_swapChain);

		CFactory<CColorTexture>::Instance().Create(0, m_colorTexture);
		CFactory<CNormalTexture>::Instance().Create(0, m_normalTexture);
		CFactory<CDepthStencilTexture>::Instance().Create(0, m_depthTexture);

		CFactory<CLastComputeShader>::Instance().Create(0, m_last_cs);

		if (m_manager) {
			m_manager->RegistBack(this);
		}
	}
	~CLastPass() {}
};


#endif