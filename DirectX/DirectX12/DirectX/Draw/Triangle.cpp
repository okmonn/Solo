#include "Triangle.h"
#include "../Device.h"
#include "../Command/List.h"
#include <tchar.h>

// ���_�̍ő吔
#define VERTEX_MAX 3

// �R���X�g���N�^
Triangle::Triangle(std::weak_ptr<Device>dev, std::weak_ptr<List>list) :
	resource(nullptr), data(nullptr)
{
	this->dev = dev;
	this->list = list;

	vertex.clear();
	view = {};
	
	CreateResource();
}

// �f�X�g���N�^
Triangle::~Triangle()
{
	Release(resource);
}

// ���\�[�X�̐���
HRESULT Triangle::CreateResource(void)
{
	//���_�̐������������m��
	vertex.resize(VERTEX_MAX);
	vertex[0] = { { 200.0f, 200.0f, 0.0f }, { 0.0f, 0.0f } };//����
	vertex[1] = { { 250.0f, 200.0f, 0.0f }, { 1.0f, 0.0f } };//�E��
	vertex[2] = { { 250.0f, 250.0f, 0.0f }, { 1.0f, 1.0f } };//�E��

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
	desc.Width            = sizeof(Vertex) * vertex.size();
	desc.Height           = 1;
	desc.DepthOrArraySize = 1;
	desc.MipLevels        = 1;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count = 1;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�O�p�`�̒��_���\�[�X�̐����F���s\n"));
		return result;
	}

	//���M�͈�
	D3D12_RANGE range = { 0,0 };

	//�}�b�s���O
	result = resource->Map(0, &range, reinterpret_cast<void**>(&data));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�O�p�`�̃��\�[�X�}�b�s���O�F���s\n"));
		return result;
	}

	//���_�f�[�^�̃R�s�[
	memcpy(data, vertex.data(), sizeof(Vertex) * vertex.size());

	//�A���}�b�v
	resource->Unmap(0, nullptr);

	//���_�o�b�t�@�ݒ�p�\���̂̐ݒ�
	view.BufferLocation = resource->GetGPUVirtualAddress();
	view.SizeInBytes    = sizeof(Vertex) * vertex.size();
	view.StrideInBytes  = sizeof(Vertex);

	return result;
}

// �`��
void Triangle::Draw(void)
{
	//���_�o�b�t�@�r���[�̃Z�b�g
	list.lock()->GetList()->IASetVertexBuffers(0, 1, &view);

	//�g�|���W�[�^�C�v�̃Z�b�g
	list.lock()->GetList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�`��
	list.lock()->GetList()->DrawInstanced(VERTEX_MAX, 1, 0, 0);
}
