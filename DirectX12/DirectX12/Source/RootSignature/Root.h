#pragma once
#include "../BaseObj/Obj.h"
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

	// ���[�g�V�O�l�`���̐���
	HRESULT CreateRoot(const D3D12_ROOT_PARAMETER* range, UINT num);

	// ���b�Z�[�W�̎擾
	ID3DBlob* GetMsg(void) const {
		return signature;
	}
	// �G���[���b�Z�[�W�̎擾
	ID3DBlob* GetError(void) const {
		return error;
	}
	// ���[�g�V�O�l�`���̎擾
	ID3D12RootSignature* Get(void) const {
		return root;
	}

private:
	// ���[�g�V�O�l�`���̐���
	HRESULT CreateRoot(void);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// ���b�Z�[�W
	ID3DBlob * signature;

	// �G���[���b�Z�[�W
	ID3DBlob* error;

	// ���[�g�V�O�l�`��
	ID3D12RootSignature * root;
};

