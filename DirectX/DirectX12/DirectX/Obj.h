#pragma once
#ifndef _NOT_USE_D3D12
#include <d3d12.h>
#endif

// �����[�X�}�N��
#define Release(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }

class Obj
{
public:
	// �R���X�g���N�^
	Obj() {
	}
	// �f�X�g���N�^
	virtual ~Obj() {
	}

protected:
	// �Q�ƌ���
	HRESULT result;
};
