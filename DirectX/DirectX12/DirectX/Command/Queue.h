#pragma once
#include "Command.h"

class Queue :
	public Command
{
public:
	// �R���X�g���N�^
	Queue(std::weak_ptr<Device>dev);
	// �f�X�g���N�^
	~Queue();

	// �R�}���h�L���[�̎擾
	ID3D12CommandQueue* Get(void) const {
		return queue;
	}

private:
	// �R�}���h�L���[�̐���
	HRESULT CreateQueue(void);


	// �R�}���h�L���[
	ID3D12CommandQueue * queue;
};
