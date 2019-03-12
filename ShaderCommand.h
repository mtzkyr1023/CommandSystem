#ifndef _SHADERCOMMAND_H_
#define _SHADERCOMMAND_H_

#include "ResourceCommand.h"

#include "ModelShader.h"
#include "LastShader.h"

class CCreateModelShader : public CResourceCommand {
protected:
	bool Internal() {
		bool res;

		std::shared_ptr<CStaticModelVertexShader> static_vs;
		std::shared_ptr<CModelPixelShader> model_ps;
		std::shared_ptr<CLastComputeShader> last_cs;

		CFactory<CStaticModelVertexShader>::Instance().Create(0, static_vs);
		CFactory<CModelPixelShader>::Instance().Create(0, model_ps);
		CFactory<CLastComputeShader>::Instance().Create(0, last_cs);

		res = static_vs->Initialize();
		if (!res)
			return false;

		res = model_ps->Initialize();
		if (!res)
			return false;

		res = last_cs->Initialize();
		if (!res)
			return false;

		return true;
	}

public:
	CCreateModelShader() {}
};

#endif