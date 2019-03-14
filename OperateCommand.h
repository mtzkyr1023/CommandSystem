#ifndef _OPERATECOMMAND_H_
#define _OPERATECOMMAND_H_

#include <DirectXMath.h>

#include "Command.h"
#include "Factory.h"

#include "BackBuffer.h"
#include "SwapChain.h"

class COperateCommand : public CCommand {
private:
	static CCommandManager* m_manager;

protected:
	COperateCommand() {
		if (m_manager) {
			m_manager->RegistBack(this);
		}
	}

public:
	virtual ~COperateCommand() {

	}

	static void SetManager(CCommandManager* manager) {
		m_manager = manager;
	}
};

#endif