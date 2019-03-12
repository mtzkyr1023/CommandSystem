#ifndef _CONSTBUFFER_H_
#define _CONSTBUFFER_H_

#include "Buffer.h"

class CMatrixBuffer : public CBuffer {
public:
	CMatrixBuffer() {}
	~CMatrixBuffer() {}

	bool Initialize();
};

#endif