#pragma once
#include "Obj.h"
#include <memory>

class Device;
class Swap;
class Root;

class Pipe :
	public Obj
{
public:
	// �R���X�g���N�^
	Pipe(std::weak_ptr<Device>dev, std::weak_ptr<Swap>swap, std::weak_ptr<Root>root);
	// �f�X�g���N�^
	~Pipe();

	// �p�C�v���C���̎擾
	ID3D12PipelineState* Get(void) const {
		return pipe;
	}

private:
	// �p�C�v���C���̐���
	HRESULT CreatePipe(void);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �X���b�v�`�F�C��
	std::weak_ptr<Swap>swap;

	// ���[�g�V�O�l�`��
	std::weak_ptr<Root>root;

	// �p�C�v���C��
	ID3D12PipelineState* pipe;
};

