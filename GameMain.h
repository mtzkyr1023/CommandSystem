#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "ResourceCommand.h"
#include "OperateCommand.h"
#include "GraphicCommand.h"

class GameMain {
private:
	CCommandManager m_gManager;
	CCommandManager m_oManager;
	CCommandManager m_rManager;

public:
	GameMain() {
	}

	bool Init(HWND hwnd, int width, int height);

	bool Run();
};

#endif