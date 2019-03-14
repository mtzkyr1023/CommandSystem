#include "GameMain.h"


#include "ShaderCommand.h"
#include "BufferCommand.h"
#include "MoveCommand.h"
#include "MatrixCommand.h"
#include "TextureCommand.h"


bool GameMain::Init(HWND hwnd, int width, int height) {
	CResourceCommand::SetManager(&m_rManager);
	COperateCommand::SetManager(&m_oManager);
	CGraphicCommand::SetManager(&m_gManager);

	CResourceCommand* ptr = new CCreateBackBuffer(hwnd, width, height, 1, true);
	ptr = new CCreateMatrixBuffer();
	ptr = new CCreateModelShader();
	ptr = new CCreateModelPassTexture(width, height);
	ptr = new CCreateFontTexture("tex/Cica_font.bmp");

	COperateCommand* ope = new CViewMatrixUpdate();
	ope = new CProjMatrixUpdate(XM_PIDIV2, 4.0f / 3.0f, 10.0f, 1000.0f);

	CGraphicCommand* gra = new CModelPass();
	gra = new CLastPass();

	return true;
}

bool GameMain::Run() {
	if (!m_rManager.RunCommand())
		return false;

	if (!m_oManager.RunCommand())
		return false;

	if (!m_gManager.RunCommand())
		return false;

	return true;
}