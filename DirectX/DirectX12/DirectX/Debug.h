#pragma once
#include "Obj.h"

class Debug :
	public Obj
{
public:
	// �R���X�g���N�^
	Debug();
	// �f�X�g���N�^
	~Debug();

private:
	// �f�o�b�O
	ID3D12Debug * debug;
};
