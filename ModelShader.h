#ifndef _MODELSHADER_H_
#define _MODELSHADER_H_

#include "Shader.h"

class CStaticModelVertexShader : public CVertexShader {
public:
	CStaticModelVertexShader() {}
	~CStaticModelVertexShader() {}

	bool Initialize();
};

class CModelPixelShader : public CPixelShader {
public:
	CModelPixelShader() {}
	~CModelPixelShader() {}

	bool Initialize();
};

#endif