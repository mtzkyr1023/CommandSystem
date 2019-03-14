#ifndef _RESOURCECOMMAND_H_
#define _RESOURCECOMMAND_H_

#include "Command.h"
#include "Factory.h"

class CResourceCommand : public CCommand {
private:
	static CCommandManager* m_manager;

protected:
	CResourceCommand() {
		m_enableTime = 0;
		if (m_manager) {
			m_manager->RegistBack(this);
		}
	}

public:
	virtual ~CResourceCommand() {}

	static void SetManager(CCommandManager* manager) {
		m_manager = manager;
	}
};


#endif