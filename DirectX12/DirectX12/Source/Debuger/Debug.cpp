#include "Debug.h"
#include <tchar.h>

// �R���X�g���N�^
Debug::Debug() : 
	debug(nullptr)
{
	Create();
}

// �f�X�g���N�^
Debug::~Debug()
{
	Release(debug);
}

// ����
HRESULT Debug::Create(void)
{
	result = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�f�o�b�K�̐����F���s\n"));
		return result;
	}

	debug->EnableDebugLayer();

	return result;
}
