#ifndef _BUFFERCOMMAND_H_
#define _BUFFERCOMMAND_H_

#include <DirectXMath.h>
using namespace DirectX;
#include "ResourceCommand.h"

#include "ConstBuffer.h"

class CCreateMatrixBuffer : public CResourceCommand {
protected:
	bool Internal() {
		bool res;
		std::shared_ptr<CMatrixBuffer> m_viewBuffer;
		std::shared_ptr<CMatrixBuffer> m_projBuffer;
		std::shared_ptr<XMFLOAT4X4> m_viewMatrix;
		std::shared_ptr<XMFLOAT4X4> m_projMatrix;

		CFactory<CMatrixBuffer>::Instance().Create(0, m_viewBuffer);
		CFactory<CMatrixBuffer>::Instance().Create(1, m_projBuffer);

		res = m_viewBuffer->Initialize();
		if (!res) {
			MessageBox(NULL, "failed creating view matrix buffer.", "CMatrixBuffer.cpp", MB_OK);
			return false;
		}

		res = m_projBuffer->Initialize();
		if (!res) {
			MessageBox(NULL, "failed creating view matrix buffer.", "CMatrixBuffer.cpp", MB_OK);
			return false;
		}

		return true;
	}
};

#endif