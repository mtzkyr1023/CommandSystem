#ifndef _SHADER_H_
#define _SHADER_H_

#include "Device.h"

class CVertexShader : public CDeviceUser {
protected:
	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3D11InputLayout> m_layout;

public:
	virtual ~CVertexShader() {}

	virtual bool Initialize() = 0;

	virtual void Set() {
		m_context->IASetInputLayout(m_layout.Get());

		m_context->VSSetShader(m_vertexShader.Get(), NULL, 0);
	}
};

class CPixelShader : public CDeviceUser {
protected:
	ComPtr<ID3D11PixelShader> m_pixelShader;
	
public:
	virtual ~CPixelShader() {}

	virtual bool Initialize() = 0;

	virtual void Set() {
		m_context->PSSetShader(m_pixelShader.Get(), NULL, 0);
	}
};

class CComputeShader : public CDeviceUser {
protected:
	ComPtr<ID3D11ComputeShader> m_computeShader;

public:
	virtual ~CComputeShader() {}

	virtual bool Initialize() = 0;

	virtual void Set() {
		m_context->CSSetShader(m_computeShader.Get(), NULL, 0);
	}
};

#endif