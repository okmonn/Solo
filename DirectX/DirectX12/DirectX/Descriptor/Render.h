#pragma once
#include "Descriptor.h"
#include <vector>

class Render :
	public Descriptor
{
public:
	// �R���X�g���N�^
	Render(std::weak_ptr<Device>dev, std::weak_ptr<List>list, std::weak_ptr<Swap>swap);
	// �f�X�g���N�^
	~Render();

	// �����_�[�^�[�Q�b�g�̃Z�b�g
	void SetRender(ID3D12DescriptorHeap* depth);

	// ���\�[�X�̎擾
	ID3D12Resource* GetResource(UINT index) const {
		return resource[index];
	}
	// ���\�[�X�̎擾
	std::vector<ID3D12Resource*>GetResource(void) const {
		return resource;
	}

private:
	// ���\�[�X�̐���
	HRESULT CreateResource(void);


	// ���\�[�X
	std::vector<ID3D12Resource*>resource;
};

