#pragma once
#include "Obj.h"
#include <memory>

class Device;
class Swap;
class Root;
class Compiler;

class Pipe :
	public Obj
{
public:
	// �R���X�g���N�^
	Pipe(const LPCWSTR& path, std::weak_ptr<Device>dev, std::weak_ptr<Swap>swap, std::weak_ptr<Root>root, std::weak_ptr<Compiler>com,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE type = D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	// �f�X�g���N�^
	~Pipe();

	// �p�C�v���C���̎擾
	ID3D12PipelineState* Get(void) const {
		return pipe;
	}

private:
	// �p�C�v���C���̐���
	HRESULT CreatePipe(void);


	// �p�X
	LPCWSTR path;

	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �X���b�v�`�F�C��
	std::weak_ptr<Swap>swap;

	// ���[�g�V�O�l�`��
	std::weak_ptr<Root>root;

	// �V�F�[�_�R���p�C���[
	std::weak_ptr<Compiler>com;

	// �p�C�v���C��
	ID3D12PipelineState* pipe;

	// �v���~�e�B�u�^�C�v
	D3D12_PRIMITIVE_TOPOLOGY_TYPE type;
};

