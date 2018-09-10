#pragma once
#include "../BaseObj/Obj.h"
#include <memory>

class Device;
class Queue;

class Fence :
	public Obj
{
public:
	// �R���X�g���N�^
	Fence(std::weak_ptr<Device>dev, std::weak_ptr<Queue>queue);
	// �f�X�g���N�^
	~Fence();

	// �ҋ@����
	void Wait(void);

	// �t�F���X�̎擾
	ID3D12Fence* Get(void) const {
		return fence;
	}

	// �t�F���X�l�̎擾
	UINT64 GetCnt(void) const {
		return cnt;
	}

private:
	// �t�F���X�̎擾
	HRESULT CreateFence(void);

	// �t�F���X�C�x���g�̐���
	HRESULT CreateEvt(void);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �R�}���h�L���[
	std::weak_ptr<Queue>queue;

	//�t�F���X
	ID3D12Fence* fence;

	//�t�F���X�C�x���g
	HANDLE handle;

	//�t�F���X�l
	UINT64 cnt;
};

