#pragma once
#include "../Descriptor/Descriptor.h"
#include "../../etc/Typedef.h"
#include <vector>

class Triangle :
	public Descriptor
{
public:
	// �R���X�g���N�^
	Triangle(std::weak_ptr<Device>dev, std::weak_ptr<List>list);
	// �f�X�g���N�^
	~Triangle();

	// �`��
	void Draw(void);

	// ���_���\�[�X�̎擾
	ID3D12Resource* GetResource(void) const {
		return resource;
	}

private:
	// ���\�[�X�̐���
	HRESULT CreateResource(void);


	// ���_
	std::vector<Vertex>vertex;

	// ���\�[�X
	ID3D12Resource * resource;

	// ���M�f�[�^
	UINT8* data;

	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW view;
};

