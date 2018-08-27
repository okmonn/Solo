#include "Constant.h"
#include "../../Window/Window.h"
#include "../Device.h"
#include "../Command/List.h"
#include <tchar.h>

#define RESOURCE_MAX 2

// �R���X�g���N�^
Constant::Constant(std::weak_ptr<Window>win, std::weak_ptr<Device>dev, std::weak_ptr<List>list) : 
	win(win)
{
	this->dev  = dev;
	this->list = list;

	resource.clear();
	resource.resize(RESOURCE_MAX);
	data.clear();
	data.resize(RESOURCE_MAX);
	wvp = {};
	window = {static_cast<FLOAT>(this->win.lock()->GetX()), static_cast<FLOAT>(this->win.lock()->GetY())};
	
	SetWVP();
	CreateHeap(RESOURCE_MAX, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
	CreateResource(0, ((sizeof(WVP) + 0xff) &~0xff));
	CreateResource(1, ((sizeof(DirectX::XMFLOAT2) + 0xff) &~0xff));
	CreateView(0, (sizeof(WVP) + 0xff) &~0xff, sizeof(WVP));
	CreateView(1, (sizeof(DirectX::XMFLOAT2) + 0xff) &~0xff, sizeof(DirectX::XMFLOAT2));
}

// �f�X�g���N�^
Constant::~Constant()
{
	for (UINT i = 0; i < resource.size(); ++i)
	{
		if (resource[i] != nullptr)
		{
			resource[i]->Unmap(0, nullptr);
		}

		Release(resource[i]);
	}
	Release(heap);
}

// WVP�̃Z�b�g
void Constant::SetWVP(void)
{
	//�_�~�[�錾
	FLOAT pos = 0.0f;
	DirectX::XMMATRIX view   = DirectX::XMMatrixIdentity();
	//�J�����̈ʒu
	DirectX::XMVECTOR eye    = { 0, pos,  -1 };
	//�J�����̏œ_
	DirectX::XMVECTOR target = { 0, pos,   0 };
	//�J�����̏����
	DirectX::XMVECTOR upper  = { 0, 1,     0 };

	wvp.view = DirectX::XMMatrixLookAtLH(eye, target, upper);

	wvp.projection = DirectX::XMMatrixPerspectiveFovLH(RAD(90.0f), ((static_cast<FLOAT>(win.lock()->GetX()) / static_cast<FLOAT>(win.lock()->GetY()))), 0.5f, 500.0f);

	//�X�V
	wvp.world      = DirectX::XMMatrixIdentity();
}

// ���\�[�X�̐���
HRESULT Constant::CreateResource(UINT index, UINT64 size)
{
	//�v���p�e�B�ݒ�p�\���̂̐ݒ�
	D3D12_HEAP_PROPERTIES prop = {};
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.CreationNodeMask     = 1;
	prop.VisibleNodeMask      = 1;

	//���\�[�X�ݒ�p�\���̂̐ݒ�
	D3D12_RESOURCE_DESC desc = {};
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Width            = size;
	desc.Height           = 1;
	desc.DepthOrArraySize = 1;
	desc.MipLevels        = 1;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count = 1;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource[index]));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�萔�o�b�t�@�̃��\�[�X�̐����F���s\n"));
	}

	return result;
}

// ���\�[�X�r���[�̐���
HRESULT Constant::CreateView(UINT index, UINT size, UINT stride)
{
	//�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += this->size * index;

	//�萔�o�b�t�@�r���[�ݒ�p�\���̂̐ݒ�
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
	desc.SizeInBytes    = size;
	desc.BufferLocation = resource[index]->GetGPUVirtualAddress();

	//���M�͈�
	D3D12_RANGE range = { 0, 0 };

	//�萔�o�b�t�@�r���[����
	dev.lock()->Get()->CreateConstantBufferView(&desc, handle);

	//�}�b�s���O
	result = resource[index]->Map(0, &range, (void**)(&data[index]));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�萔�o�b�t�@�̃��\�[�X�}�b�s���O�F���s\n"));
		return result;
	}

	//�R�s�[
	memcpy(data[index], &wvp, stride);

	return result;
}

// WVP�̍X�V
void Constant::UpDataWVP(void)
{
	//��]
	static float angle = 0.0f;
	//�s��X�V
	wvp.world = DirectX::XMMatrixRotationY(RAD(angle));

	//�s��f�[�^�X�V
	memcpy(data[0], &wvp, sizeof(WVP));

	angle++;
}

// Image�̍X�V
void Constant::UpDataWindow(void)
{
	memcpy(data[1], &window, sizeof(DirectX::XMFLOAT2));
}

// �萔�o�b�t�@�̃Z�b�g
void Constant::SetConstant(UINT rootIndex, UINT index)
{
	// �n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += size * index;

	//�q�[�v�̃Z�b�g
	list.lock()->GetList()->SetDescriptorHeaps(1, &heap);

	//���[�g�V�O�l�`���Ƃ̊֘A�Â�
	list.lock()->GetList()->SetGraphicsRootDescriptorTable(rootIndex, handle);
}
