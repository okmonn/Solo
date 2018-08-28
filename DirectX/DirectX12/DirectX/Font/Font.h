#pragma once
#include "../Descriptor/Descriptor.h"
#include "../../etc/Typedef.h"
#include <map>
#include <vector>
#include <string>

class Font :
	public Descriptor
{
	// �萔�o�b�t�@
	struct Con {
		//�q�[�v
		ID3D12DescriptorHeap* heap;
		//���\�[�X
		ID3D12Resource* resource;
	};

	// BMP�f�[�^
	struct BMP {
		//�f�[�^
		std::vector<BYTE>image;
		//�T�C�YX
		LONG x;
		//�T�C�YY
		LONG y;
		//���_�f�[�^
		std::vector<Vertex>vertex;
		//���\�[�X
		ID3D12Resource* resource;
		//���_�o�b�t�@�r���[
		D3D12_VERTEX_BUFFER_VIEW view;
		//���M�f�[�^
		UINT8* data;
		//�萔�o�b�t�@
		Con con;
	};

public:
	// �R���X�g���N�^
	Font(std::weak_ptr<Device>dev, std::weak_ptr<List>list);
	Font(const std::wstring& path, std::weak_ptr<Device>dev, std::weak_ptr<List>list);
	// �f�X�g���N�^
	~Font();

	// �t�H���g�T�C�Y�̎擾
	LONG GetSize(void) const {
		return size;
	}
	// �t�H���g�T�C�Y�̃Z�b�g
	void SetSize(const LONG& i) {
		size = i;
	}

	// �t�H���g�̑����̎擾
	LONG GetWeight(void) const {
		return weight;
	}
	// �t�H���g�̑����̃Z�b�g
	void SetWeight(const LONG& i) {
		weight = i;
	}

private:
	// �t�H���g�̐���
	HRESULT CreateFnt(void);

	// �q�[�v�̐���
	HRESULT CreateConHeap(void);

	// ���\�[�X�̐���
	HRESULT CreateConResource(void);

	// �V�F�[�_���\�[�X�r���[�̐���
	HRESULT CreateShaderView(void);

	// �t�H���g�`��
	HRESULT DrawFont(void);


	// �t�H���g
	HFONT font;

	// �O�̃t�H���g
	HFONT old;

	// �t�H���g�T�C�Y
	LONG size;

	// �t�H���g�̑���
	LONG weight;

	// �K�����x��
	int level;

	// �t�H���g��
	std::wstring name;

	// 
	HDC hdc;

	// 
	TEXTMETRIC tm;

	// 
	GLYPHMETRICS gm;

	// 
	BMP bmp;
};

