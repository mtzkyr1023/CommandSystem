#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Device.h"

class CBuffer : public CDeviceUser {
protected:
	ComPtr<ID3D11Buffer> m_buffer;

public:
	virtual ~CBuffer() {}

	virtual bool Initialize() = 0;

	ComPtr<ID3D11Buffer> GetBuffer() { return m_buffer; }

	virtual ID3D11ShaderResourceView* GetSRV() { return NULL; }
	virtual ID3D11UnorderedAccessView* GetUAV() { return NULL; }
};

#endif