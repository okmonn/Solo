#include "List.h"
#include "../../Device/Device.h"
#include <tchar.h>

// �R���X�g���N�^
List::List(std::weak_ptr<Device>dev) : 
	allo(nullptr), list(nullptr)
{
	this->dev = dev;

	CreateAllo();
	CreateList();
}

// �f�X�g���N�^
List::~List()
{
	Release(list);
	Release(allo);
}

// �R�}���h�A���P�[�^�̐���
HRESULT List::CreateAllo(void)
{
	result = dev.lock()->Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allo));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�R�}���h�A���P�[�^�̐����F���s\n"));
	}

	return result;
}

// �R�}���h���X�g�̐���
HRESULT List::CreateList(void)
{
	result = dev.lock()->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT, allo, nullptr, IID_PPV_ARGS(&list));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�R�}���h���X�g�̐����F���s\n"));
		return result;
	}

	Close();

	return result;
}

// ���Z�b�g
void List::Reset(ID3D12PipelineState * pipe)
{
	//�R�}���h�A���P�[�^�̃��Z�b�g
	allo->Reset();

	//�R�}���h���X�g�̃��Z�b�g
	list->Reset(allo, pipe);
}

// ���[�g�V�O�l�`���̃Z�b�g
void List::SetRoot(ID3D12RootSignature * root)
{
	list->SetGraphicsRootSignature(root);
}

// �p�C�v���C���̃Z�b�g
void List::SetPipe(ID3D12PipelineState * pipe)
{
	list->SetPipelineState(pipe);
}

// �r���[�|�[�g�̃Z�b�g
void List::SetViewPort(const D3D12_VIEWPORT & viewport)
{
	list->RSSetViewports(1, &viewport);
}

// �V�U�[�̃Z�b�g
void List::SetScissor(const RECT & scissor)
{
	list->RSSetScissorRects(1, &scissor);
}

// �R�}���h���X�g�̃N���[�Y
void List::Close(void)
{
	list->Close();
}
