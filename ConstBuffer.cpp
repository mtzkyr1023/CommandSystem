#include "ConstBuffer.h"

bool CMatrixBuffer::Initialize() {
	HRESULT res;
	D3D11_BUFFER_DESC bufDesc;
	ZeroMemory(&bufDesc, sizeof(bufDesc));

	bufDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufDesc.ByteWidth = sizeof(float) * 16;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufDesc.MiscFlags = 0;
	bufDesc.StructureByteStride = 0;

	res = m_device->CreateBuffer(&bufDesc, NULL, m_buffer.ReleaseAndGetAddressOf());
	if (FAILED(res))
		return false;

	return true;
}