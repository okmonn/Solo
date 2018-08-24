#include "Queue.h"
#include "../Device.h"
#include <tchar.h>

// �R���X�g���N�^
Queue::Queue(std::weak_ptr<Device>dev) : 
	queue(nullptr)
{
	this->dev = dev;

	CreateQueue();
}

// �f�X�g���N�^
Queue::~Queue()
{
	Release(queue);
}

// �R�}���h�L���[�̐���
HRESULT Queue::CreateQueue(void)
{
	//�R�}���h�L���[�ݒ�p�\����
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Flags    = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Type     = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;

	result = dev.lock()->Get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�R�}���h�L���[�̐����F���s\n"));
	}

	return result;
}
