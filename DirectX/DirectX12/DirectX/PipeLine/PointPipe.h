#pragma once
#include "../Obj.h"
#include <memory>

class Device;
class Swap;
class Root;
class Compiler;

class PointPipe :
	public Obj
{
public:
	// �R���X�g���N�^
	PointPipe();
	// �f�X�g���N�^
	~PointPipe();

private:
	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �X���b�v�`�F�C��
	std::weak_ptr<Swap>swap;

	// ���[�g�V�O�l�`��
	std::weak_ptr<Root>root;
};

