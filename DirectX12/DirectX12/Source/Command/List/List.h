#pragma once
#include "../Command.h"

class List :
	public Command
{
public:
	// �R���X�g���N�^
	List(std::weak_ptr<Device>dev);
	// �f�X�g���N�^
	~List();

	// ���Z�b�g
	void Reset(ID3D12PipelineState* pipe);

	// ���[�g�V�O�l�`���̃Z�b�g
	void SetRoot(ID3D12RootSignature* root);

	// �p�C�v���C���̃Z�b�g
	void SetPipe(ID3D12PipelineState* pipe);

	// �r���[�|�[�g�̃Z�b�g
	void SetViewPort(const D3D12_VIEWPORT & viewport);

	// �V�U�[�̃Z�b�g
	void SetScissor(const RECT& scissor);

	// �R�}���h���X�g�̃N���[�Y
	void Close(void);

	// �R�}���h�A���P�[�^
	ID3D12CommandAllocator* GetAllo(void) const {
		return allo;
	}

	// �R�}���h���X�g
	ID3D12GraphicsCommandList* GetList(void) const {
		return list;
	}

private:
	// �R�}���h�A���P�[�^�̐���
	HRESULT CreateAllo(void);

	// �R�}���h���X�g�̐���
	HRESULT CreateList(void);


	// �R�}���h�A���P�[�^
	ID3D12CommandAllocator * allo;

	// �R�}���h���X�g
	ID3D12GraphicsCommandList* list;
};

