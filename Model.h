#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include <DirectXMath.h>

#include "Device.h"

class Model : public CDeviceUser {
protected:
	std::vector<ComPtr<ID3D11Buffer>> m_vertexBuffer;
	std::vector<ComPtr<ID3D11Buffer>> m_indexBuffer;
	UINT m_stride;

public:
	virtual bool Initialize() {
		struct Vertex {
			float pos[3];
			float nor[3];
			float tex[2];
		};

		Vertex v[3];
		memset(v, 0, sizeof(v));

		v[0].pos[0] = -1.0f;
		v[0].pos[1] = -1.0f;
		v[0].pos[2] = 0.0f;
		v[1].pos[0] = 1.0f;
		v[1].pos[1] = -1.0f;
		v[1].pos[2] = 0.0f;
		v[2].pos[0] = 0.0f;
		v[2].pos[1] = 1.0f;
		v[2].pos[2] = 0.0f;

		HRESULT res;
		D3D11_BUFFER_DESC bufDesc;
		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&bufDesc, sizeof(bufDesc));
		ZeroMemory(&initData, sizeof(initData));

		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.ByteWidth = sizeof(Vertex) * 3;
		bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = 0;
		bufDesc.StructureByteStride = 0;

		initData.pSysMem = v;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> tmpBuf;
		res = m_device->CreateBuffer(&bufDesc, &initData, tmpBuf.ReleaseAndGetAddressOf());
		m_vertexBuffer.push_back(tmpBuf);


		return true;
	}

	virtual void Draw() {
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		UINT stride = 32;
		UINT offset = 0;
		m_context->IASetVertexBuffers(0, 1, m_vertexBuffer[0].GetAddressOf(), &stride, &offset);

		m_context->Draw(3, 0);
	}
};

class StaticModel : public Model {
private:
	struct Vertex {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 nor;
		DirectX::XMFLOAT2 tex;
	};

public:
	StaticModel() {
		m_stride = 0;
		m_stride = sizeof(Vertex);
	}

	bool Initialize(const char* filename);

	void Draw();
};

#endif