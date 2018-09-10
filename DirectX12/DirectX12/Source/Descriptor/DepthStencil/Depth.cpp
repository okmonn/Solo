#include "Depth.h"
#include "../../Window/Window.h"
#include "../../Device/Device.h"
#include "../../Command/List/List.h"
#include "../../SwapChain/Swap.h"
#include <tchar.h>

// ���\�[�X��
#define RESOURCE_MAX 1

// �R���X�g���N�^
Depth::Depth(std::weak_ptr<Window>win, std::weak_ptr<Device>dev, std::weak_ptr<List>list) :
	win(win)
{
	this->dev  = dev;
	this->list = list;

	CreateResource();
	CreateView();
}

// �f�X�g���N�^
Depth::~Depth()
{
	Release(resource);
	Release(heap);
}

// ���\�[�X�̐���
HRESULT Depth::CreateResource(void)
{
	result = CreateHeap(RESOURCE_MAX, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	if (FAILED(result))
	{
		return result;
	}

	//�v���p�e�B�ݒ�p�\���̂̐ݒ�
	D3D12_HEAP_PROPERTIES prop = {};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.CreationNodeMask     = 0;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT;
	prop.VisibleNodeMask      = 0;

	//���\�[�X�ݒ�p�\���̂̐ݒ�
	D3D12_RESOURCE_DESC desc = {};
	desc.Dimension          = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment          = 0;
	desc.Width              = win.lock()->GetX();
	desc.Height             = win.lock()->GetY();
	desc.DepthOrArraySize   = 1;
	desc.MipLevels          = 0;
	desc.Format             = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
	desc.SampleDesc.Count   = 1;
	desc.SampleDesc.Quality = 0;
	desc.Flags              = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	desc.Layout             = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;

	//�N���A�l�ݒ�p�\���̂̐ݒ�
	D3D12_CLEAR_VALUE clear = {};
	clear.Format               = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	clear.DepthStencil.Depth   = 1.0f;
	clear.DepthStencil.Stencil = 0;

	result = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_DEPTH_WRITE, &clear, IID_PPV_ARGS(&resource));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�[�x�X�e���V���̃��\�[�X�̐����F���s\n"));
	}

	return result;
}

// ���\�[�X�r���[�̐���
HRESULT Depth::CreateView(void)
{
	//�[�x�X�e���V���r���[�ݒ�p�\���̂̐ݒ�
	D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};
	desc.Format        = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	desc.ViewDimension = D3D12_DSV_DIMENSION::D3D12_DSV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;
	desc.Flags         = D3D12_DSV_FLAGS::D3D12_DSV_FLAG_NONE;

	//�[�x�X�e���V���r���[����
	dev.lock()->Get()->CreateDepthStencilView(resource, &desc, GetHeap()->GetCPUDescriptorHandleForHeapStart());

	return result;
}

// �[�x�X�e���V���̃Z�b�g
void Depth::SetDepth(void)
{
	//�[�x�X�e���V���q�[�v�̐擪�n���h���̎擾
	D3D12_CPU_DESCRIPTOR_HANDLE d_handle = heap->GetCPUDescriptorHandleForHeapStart();

	//�[�x�X�e���V���r���[�̃N���A
	list.lock()->GetList()->ClearDepthStencilView(d_handle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}
