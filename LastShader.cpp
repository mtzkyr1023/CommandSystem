#include "LastShader.h"

#include "shader/last_cs.h"

bool CLastComputeShader::Initialize() {
	HRESULT res;

	res = m_device->CreateComputeShader(g_last_cs_main, sizeof(g_last_cs_main), NULL, m_computeShader.ReleaseAndGetAddressOf());


	return true;
}
