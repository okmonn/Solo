#pragma once
#include "../BaseObj/Obj.h"
#include <memory>

class Device;
class List;

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

	// �q�[�v�T�C�Y�̎擾
	UINT GetSize(void) const {
		return size;
	}

protected:
	// �q�[�v�̐���
	HRESULT CreateHeap(UINT num, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �R�}���h���X�g
	std::weak_ptr<List>list;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// �q�[�v�T�C�Y
	UINT size;
};

