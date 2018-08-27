#include "Descriptor.h"
#include "../Device.h"
#include "../Command/List.h"
#include "../Swap.h"
#include <tchar.h>

// �R���X�g���N�^
Descriptor::Descriptor() : 
	heap(nullptr), size(0)
{
}

// �f�X�g���N�^
Descriptor::~Descriptor()
{
}

// �q�[�v�̐���
HRESULT Descriptor::CreateHeap(UINT num, const D3D12_DESCRIPTOR_HEAP_TYPE & type, const D3D12_DESCRIPTOR_HEAP_FLAGS & flag)
{
	//�q�[�v�ݒ�p�\����
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Flags          = flag;
	desc.NodeMask       = 0;
	desc.NumDescriptors = num;
	desc.Type           = type;

	result = dev.lock()->Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�q�[�v�̐����F���s\n"));
		return result;
	}

	//�q�[�v�T�C�Y�̎擾
	size = dev.lock()->Get()->GetDescriptorHandleIncrementSize(type);

	return result;
}
