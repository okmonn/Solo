#pragma once
#include <d3d12.h>

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
