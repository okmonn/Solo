#pragma once
#include "../Descriptor/Descriptor.h"
#include "../etc/Vector2.h"
#include "../etc/Typedef.h"
#include <vector>
#include <map>
#include <string>

class Root;
class Pipe;
class Constant;

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
		std::vector<TexVertex>vertex;
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
	Texture(std::weak_ptr<Device>dev, std::weak_ptr<List>list, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe, std::weak_ptr<Constant>con);
	// �f�X�g���N�^
	~Texture();

	// WIC�ǂݍ���
	HRESULT LoadWIC(UINT& index, const std::string& fileName);

	// �`�揀��
	HRESULT SetDraw(UINT& index);

	// �f�B�X�N���v�^�[�̃Z�b�g
	void SetDescriptor(UINT& index);

	// �`��
	void Draw(UINT& index, const Vec2f& pos, float alpha, UINT turnX, UINT turnY);

	// �`��E�T�C�Y�w��
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, float alpha, UINT turnX, UINT turnY);

	// �`��E�T�C�Y�w��E����
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, const Vec2f& rectPos, const Vec2f& rectSize, float alpha, UINT turnX, UINT turnY);

	// �`��E���R�ό`
	void FreelyDraw(UINT& index, const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const Vec2f& pos4, float alpha, UINT turnX, UINT turnY);

	// �`��E�����E���R�ό`
	void FreelyDraw(UINT& index, const Vec2f& rectPos, const Vec2f& rectSize, const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const Vec2f& pos4, float alpha, UINT turnX, UINT turnY);

	// �폜
	void Delete(UINT& index);

private:
	// �萔�o�b�t�@�q�[�v�̐���
	HRESULT CreateHeap(UINT* index);

	// �V�F�[�_���\�[�X�r���[�̐���
	HRESULT CreateShaderView(UINT* index);

	// ���_���\�[�X�̐���
	HRESULT CreateResource(UINT* index);


	// ���[�g�V�O�l�`��
	std::weak_ptr<Root>root;

	// �p�C�v���C��
	std::weak_ptr<Pipe>pipe;

	// �萔�o�b�t�@
	std::weak_ptr<Constant>con;

	// WIC�f�[�^
	std::map<UINT*, WIC>wic;
};

namespace func {
	// ���j�R�[�h�ϊ�
	std::wstring ChangeUnicode(const CHAR* str);
}
