#ifndef _FONTTEXTURE_H_
#define _FONTTEXTURE_H_

#include <string>

#include "Texture.h"


class CFontTexture : public CTexture2D {
private:
	ComPtr<ID3D11ShaderResourceView> m_srv;

public:
	CFontTexture() {}
	~CFontTexture() {}

	bool Initialize(const char* filename);

	ID3D11ShaderResourceView* GetSRV() { return m_srv.Get(); }
};


#endif