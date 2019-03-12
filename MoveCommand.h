#ifndef _MOVECOMMAND_H_
#define _MOVECOMMAND_H_

#include "OperateCommand.h"
using namespace DirectX;

class COperateMove : public COperateCommand {
protected:
	std::shared_ptr<XMFLOAT3> m_pos;
	XMFLOAT3 m_dir;
	float m_speed;

protected:
	bool Internal() {
		m_pos->x += m_dir.x * m_speed;
		m_pos->y += m_dir.y * m_speed;
		m_pos->z += m_dir.z * m_speed;

		return true;
	}

public:
	COperateMove(uint32_t id, int enableTime, XMFLOAT3 dir, float speed) : m_speed(speed) {
		m_enableTime = enableTime;
		CFactory<XMFLOAT3>::Instance().Create(id, m_pos);
		XMStoreFloat3(&m_dir, XMVector3Normalize(XMLoadFloat3(&dir)));
	}
	virtual ~COperateMove() {}
};

#endif