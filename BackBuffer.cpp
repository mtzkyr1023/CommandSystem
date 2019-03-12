#include "BackBuffer.h"

bool CBackBuffer::Initialize(ID3D11Texture2D* backBufferPtr) {
	HRESULT res;
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;

	ZeroMemory(&rtvDesc, sizeof(rtvDesc));
	ZeroMemory(&uavDesc, sizeof(uavDesc));

	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	res = m_device->CreateRenderTargetView(backBufferPtr, &rtvDesc, m_rtv.ReleaseAndGetAddressOf());
	if (FAILED(res))
		return false;

	uavDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	uavDesc.Texture2D.MipSlice = 0;

	res = m_device->CreateUnorderedAccessView(backBufferPtr, &uavDesc, m_uav.ReleaseAndGetAddressOf());
	if (FAILED(res))
		return false;

	return true;
}

void CBackBuffer::BeginPass(float r, float g, float b, float a) {

}