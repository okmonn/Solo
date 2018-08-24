#include "Debug.h"
#include <tchar.h>

// �R���X�g���N�^
Debug::Debug() : debug(nullptr)
{
	result = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�f�o�b�O�̐����F���s\n"));
	}

	//�f�o�b�O�̕\��������
	debug->EnableDebugLayer();
}

// �f�X�g���N�^
Debug::~Debug()
{
	Release(debug);
}
