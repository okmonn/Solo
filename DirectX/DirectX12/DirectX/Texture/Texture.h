#pragma once
#include "../Descriptor/Descriptor.h"
#include "../../etc/Vector2.h"
#include "../../etc/Typedef.h"
#include <vector>
#include <map>
#include <string>

class Texture :
	public Descriptor
{
	// �萔�o�b�t�@
	struct Con {
		//�q�[�v
		ID3D12DescriptorHeap* heap;
		//���\�[�X
		ID3D12Resource* resource;
	};

	// WIC�f�[�^
	struct WIC {
		//�萔�o�b�t�@
		Con con;
		//���_�f�[�^
		std::vector<Vertex>vertex;
		//���\�[�X
		ID3D12Resource* resource;
		//�f�R�[�h
		std::unique_ptr<uint8_t[]>decode;
		//�T�u
		D3D12_SUBRESOURCE_DATA sub;
		//���_�o�b�t�@�r���[
		D3D12_VERTEX_BUFFER_VIEW view;
		//���M�f�[�^
		UINT8* data;
	};

public:
	// �R���X�g���N�^
	Texture(std::weak_ptr<Device>dev, std::weak_ptr<List>list);
	// �f�X�g���N�^
	~Texture();

	// WIC�ǂݍ���
	HRESULT LoadWIC(UINT& index, const std::string& fileName);

	// �`��
	void Draw(UINT& index, const Vec2f& pos, UINT turnX = 0, UINT turnY = 0);

	// �`��E�T�C�Y�w��
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, UINT turnX = 0, UINT turnY = 0);

	// �`��E�T�C�Y�w��E����
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, const Vec2f& rectPos, const Vec2f& rectSize, UINT turnX = 0, UINT turnY = 0);

private:
	// �萔�o�b�t�@�q�[�v�̐���
	HRESULT CreateHeap(UINT* index);

	// �V�F�[�_���\�[�X�r���[�̐���
	HRESULT CreateShaderView(UINT* index);

	// ���_���\�[�X�̐���
	HRESULT CreateResource(UINT* index);


	// WIC�f�[�^
	std::map<UINT*, WIC>wic;
};

namespace func {
	// ���j�R�[�h�ϊ�
	std::wstring ChangeUnicode(const CHAR* str);
}
