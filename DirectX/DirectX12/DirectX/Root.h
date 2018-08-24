#pragma once
#include "Obj.h"
#include <memory>

class Device;

class Root :
	public Obj
{
public:
	// �R���X�g���N�^
	Root(std::weak_ptr<Device>dev);
	// �f�X�g���N�^
	~Root();

	// ���_�V�F�[�_�̃R���p�C��
	HRESULT ComVertex(LPCWSTR fileName, LPCSTR func, LPCSTR target = "vs_5_0");
	// �s�N�Z���V�F�[�_�̃R���p�C��
	HRESULT ComPixel(LPCWSTR fileName, LPCSTR func, LPCSTR target = "ps_5_0");

	// ���b�Z�[�W�̎擾
	ID3DBlob* GetMsg(void) const {
		return signature;
	}

	// �G���[���b�Z�[�W�̎擾
	ID3DBlob* GetError(void) const {
		return error;
	}

	// ���_�V�F�[�_�̎擾
	ID3DBlob* GetVertex(void) const {
		return vertex;
	}

	// �s�N�Z���V�F�[�_�̎擾
	ID3DBlob* GetPixel(void) const {
		return pixel;
	}

	// ���[�g�V�O�l�`���̎擾
	ID3D12RootSignature* Get(void) const {
		return root;
	}

private:
	// �V���A���C�Y
	HRESULT Serialize(void);

	// ���[�g�V�O�l�`���̐���
	HRESULT CreateRoot(void);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// ���b�Z�[�W
	ID3DBlob * signature;

	// �G���[���b�Z�[�W
	ID3DBlob* error;

	// ���_�V�F�[�_
	ID3DBlob* vertex;

	// �s�N�Z���V�F�[�_
	ID3DBlob* pixel;

	// ���[�g�V�O�l�`��
	ID3D12RootSignature * root;
};

