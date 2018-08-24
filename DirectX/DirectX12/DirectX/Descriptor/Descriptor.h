#pragma once
#include "../Obj.h"
#include <memory>

class Device;
class List;
class Swap;

class Descriptor :
	public Obj
{
public:
	// �R���X�g���N�^
	Descriptor();
	// �f�X�g���N�^
	virtual ~Descriptor();

	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(void) const {
		return heap;
	}

protected:
	// �q�[�v�̐���
	HRESULT CreateHeap(const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �R�}���h���X�g
	std::weak_ptr<List>list;

	// �X���b�v�`�F�C��
	std::weak_ptr<Swap>swap;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// �q�[�v�T�C�Y
	UINT size;
};

