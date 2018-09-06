#include "render.h"
#include "../Device.h"
#include "../Command/List.h"
#include "../Swap.h"
#include <tchar.h>

//�N���A�J���[
const FLOAT color[] = {
	0.0f,
	0.0f,
	0.0f,
	0.0f
};

// �R���X�g���N�^
Render::Render(std::weak_ptr<Device>dev, std::weak_ptr<List>list, std::weak_ptr<Swap>swap)
{
	this->dev  = dev; 
	this->list = list;
	this->swap = swap;

	CreateResource();
}

// �f�X�g���N�^
Render::~Render()
{
	for (UINT i = 0; i < resource.size(); ++i)
	{
		Release(resource[i]);
	}
	Release(heap);
}

// ���\�[�X�̐���
HRESULT Render::CreateResource(void)
{
	result = CreateHeap(swap.lock()->GetBack(), D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	if (FAILED(result))
	{
		return result;
	}

	//�z��̃������m��
	resource.resize(this->swap.lock()->GetBack());

	//�����_�[�^�[�Q�b�g�ݒ�p�\����
	D3D12_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format               = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension        = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice   = 0;
	desc.Texture2D.PlaneSlice = 0;

	//�擪�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();

	for (UINT i = 0; i < resource.size(); ++i)
	{
		result = swap.lock()->Get()->GetBuffer(i, IID_PPV_ARGS(&resource[i]));
		if (FAILED(result))
		{
			OutputDebugString(_T("\n�o�b�t�@�̎擾�F���s\n"));
			break;
		}

		//�����_�[�^�[�Q�b�g�̐���
		dev.lock()->Get()->CreateRenderTargetView(resource[i], &desc, handle);

		//�n���h���ʒu�̍X�V
		handle.ptr += size;
	}

	return result;
}

// �����_�[�^�[�Q�b�g�̃Z�b�g
void Render::SetRender(ID3D12DescriptorHeap* depth)
{
	//���_�q�[�v�̐擪�n���h���̎擾
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += size * swap.lock()->Get()->GetCurrentBackBufferIndex();

	//�����_�[�^�[�Q�b�g�̃Z�b�g
	list.lock()->GetList()->OMSetRenderTargets(1, &handle, false, &depth->GetCPUDescriptorHandleForHeapStart());

	//�����_�[�^�[�Q�b�g�̃N���A
	list.lock()->GetList()->ClearRenderTargetView(handle, color, 0, nullptr);
}
