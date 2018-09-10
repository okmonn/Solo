#pragma once
#include "../BaseObj/Obj.h"

class Device :
	public Obj
{
public:
	// �R���X�g���N�^
	Device();
	// �f�X�g���N�^
	~Device();

	// �f�o�C�X�̎擾
	ID3D12Device* Get(void) const {
		return dev;
	}

private:
	// �f�o�C�X�̐���
	HRESULT CreateDev(void);


	// �f�o�C�X
	ID3D12Device * dev;

	// �@�\���x��
	D3D_FEATURE_LEVEL level;
};
