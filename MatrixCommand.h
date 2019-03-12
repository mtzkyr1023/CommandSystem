#ifndef _MATRIXCOMMAND_H_
#define _MATRIXCOMMAND_H_

#include "OperateCommand.h"
using namespace DirectX;

class CViewMatrixUpdate : public COperateCommand {
private:
	std::shared_ptr<XMFLOAT4X4> m_viewMatrix;
	std::shared_ptr<XMFLOAT3> m_viewPos;
	std::shared_ptr<XMFLOAT3> m_viewFocus;
	std::shared_ptr<XMFLOAT3> m_viewUp;

protected:
	bool Internal() {
		m_viewPos->x = 0.0f;
		m_viewPos->y = 0.0f;
		m_viewPos->z = 4.0f;
		
		XMStoreFloat4x4(m_viewMatrix.get(), XMMatrixLookAtLH(
			XMVectorSet(m_viewPos->x, m_viewPos->y, m_viewPos->z, 0.0f),
			XMVectorSet(m_viewFocus->x, m_viewFocus->y, m_viewFocus->z, 0.0f),
			XMVectorSet(m_viewUp->x, m_viewUp->y, m_viewUp->z, 1.0f)
		));

		return true;
	}

public:
	CViewMatrixUpdate() {
		CFactory<XMFLOAT4X4>::Instance().Create(0, m_viewMatrix);
		CFactory<XMFLOAT3>::Instance().Create(0, m_viewPos);
		CFactory<XMFLOAT3>::Instance().Create(1, m_viewUp);
		CFactory<XMFLOAT3>::Instance().Create(16, m_viewFocus);
		m_viewFocus->x = 0.0f; m_viewFocus->y = 0.1f; m_viewFocus->z = 0.0f;
		m_viewUp->x = 0.0f; m_viewUp->y = 1.0f; m_viewUp->z = 0.0f;
	}
};

class CProjMatrixUpdate : public COperateCommand {
private:
	std::shared_ptr<XMFLOAT4X4> m_projMatrix;

protected:
	bool Internal() {
		return true;
	}

public:
	CProjMatrixUpdate(float fov, float aspect, float nearZ, float farZ) {
		CFactory<XMFLOAT4X4>::Instance().Create(1, m_projMatrix);
		XMStoreFloat4x4(m_projMatrix.get(), XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ));
	}
};

#endif