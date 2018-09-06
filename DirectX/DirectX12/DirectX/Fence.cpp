#include "Fence.h"
#include "Device.h"
#include "Command/Queue.h"
#include <tchar.h>

// �R���X�g���N�^
Fence::Fence(std::weak_ptr<Device>dev, std::weak_ptr<Queue>queue) :
	dev(dev), queue(queue), fence(nullptr), handle(nullptr), cnt(0)
{
	CreateFence();
	CreateEvt();
}

// �f�X�g���N�^
Fence::~Fence()
{
	Release(fence);
}

// �t�F���X�̎擾
HRESULT Fence::CreateFence(void)
{
	result = dev.lock()->Get()->CreateFence(cnt, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�t�F���X�̐����F���s\n"));
		return result;
	}

	//�t�F���X�l�̍X�V
	cnt = 1;

	return result;
}

// �t�F���X�C�x���g�̐���
HRESULT Fence::CreateEvt(void)
{
	handle = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);
	if (handle == nullptr)
	{
		OutputDebugString(_T("\n�t�F���X�C�x���g�̐����F���s\n"));
		return S_FALSE;
	}

	return S_OK;
}

// �ҋ@����
void Fence::Wait(void)
{
	//�t�F���X�l�X�V
	++cnt;

	//�t�F���X�l��ύX
	{
		result = queue.lock()->Get()->Signal(fence, cnt);
		if (FAILED(result))
		{
			OutputDebugString(_T("\n�t�F���X�l�̍X�V�F���s\n"));
			return;
		}
	}

	//������ҋ@(�|�[�����O)
	while (fence->GetCompletedValue() != cnt)
	{
		//�t�F���X�C�x���g�̃Z�b�g
		result = fence->SetEventOnCompletion(cnt, handle);
		if (FAILED(result))
		{
			OutputDebugString(_T("\n�t�F���X�C�x���g�̃Z�b�g�F���s\n"));
			return;
		}

		//�t�F���X�C�x���g�̑ҋ@
		WaitForSingleObject(handle, INFINITE);
	}
}
