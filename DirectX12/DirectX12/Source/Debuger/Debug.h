#pragma once
#include "../BaseObj/Obj.h"

class Debug :
	public Obj
{
public:
	// �R���X�g���N�^
	Debug();
	// �f�X�g���N�^
	~Debug();

private:
	// ����
	HRESULT Create(void);


	// �f�o�b�O
	ID3D12Debug* debug;
};

