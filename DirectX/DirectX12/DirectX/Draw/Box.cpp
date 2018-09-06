#include "Box.h"
#include "../Device.h"
#include "../Command/List.h"
#include "../Root.h"
#include "../PipeLine/Pipe.h"
#include "../Descriptor/Constant.h"
#include <tchar.h>

// ��̒��_��
#define BOX_VERTEX 6

// �R���X�g���N�^
Box::Box(std::weak_ptr<Device>dev, std::weak_ptr<List>list, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe, std::weak_ptr<Constant>con, UINT max) :
	root(root), pipe(pipe), con(con), vertexMax(max)
{
	this->dev = dev;
	this->list = list;
	vertex.clear();
	view = {};

	CreateResource();
}

// �f�X�g���N�^
Box::~Box()
{
	if (resource != nullptr)
	{
		//resource->Unmap(0, nullptr);
	}
	Release(resource);
	Release(heap);
}

// ���\�[�X�̐���
HRESULT Box::CreateResource(void)
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
	desc.Width            = sizeof(PointVertex) * vertexMax;
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
		OutputDebugString(_T("\n�{�b�N�X�p���\�[�X�̐����F���s\n"));
		return result;
	}

	//���M�͈�
	D3D12_RANGE range = { 0,0 };

	//�}�b�s���O
	result = resource->Map(0, &range, reinterpret_cast<void**>(&data));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�{�b�N�X�p���\�[�X�̃}�b�s���O�F���s\n"));
		return result;
	}

	//���_�f�[�^�̃R�s�[
	memcpy(data, vertex.data(), sizeof(PointVertex) * vertex.size());

	//���_�o�b�t�@�ݒ�p�\���̂̐ݒ�
	view.BufferLocation = resource->GetGPUVirtualAddress();
	view.SizeInBytes    = sizeof(PointVertex) * vertex.size();
	view.StrideInBytes  = sizeof(PointVertex);

	return result;
}

// ���_�f�[�^�̒ǉ�
void Box::AddList(const Vec2f& pos, const Vec2f& size, const Vec3f& color, float alpha)
{
	vertex.push_back({ { pos.x,          pos.y,          0.0f }, { color.x, color.y, color.z, alpha } });
	vertex.push_back({ { pos.x + size.x, pos.y,          0.0f }, { color.x, color.y, color.z, alpha } });
	vertex.push_back({ { pos.x + size.x, pos.y + size.y, 0.0f }, { color.x, color.y, color.z, alpha } });
	vertex.push_back({ { pos.x + size.x, pos.y + size.y, 0.0f }, { color.x, color.y, color.z, alpha } });
	vertex.push_back({ { pos.x,          pos.y + size.y, 0.0f }, { color.x, color.y, color.z, alpha } });
	vertex.push_back({ { pos.x,          pos.y,          0.0f }, { color.x, color.y, color.z, alpha } });
}

// �`��
void Box::Draw(void)
{
	if (vertex.size() <= 0)
	{
		return;
	}

	list.lock()->GetList()->SetGraphicsRootSignature(root.lock()->Get());
	list.lock()->GetList()->SetPipelineState(pipe.lock()->Get());

	con.lock()->SetConstant();

	//���_�f�[�^�̍X�V
	memcpy(data, vertex.data(), sizeof(PointVertex) * vertex.size());

	//���_�o�b�t�@�ݒ�p�\���̂̐ݒ�
	view.BufferLocation = resource->GetGPUVirtualAddress();
	view.SizeInBytes    = sizeof(PointVertex) * vertex.size();
	view.StrideInBytes  = sizeof(PointVertex);

	//���_�o�b�t�@�r���[�̃Z�b�g
	list.lock()->GetList()->IASetVertexBuffers(0, 1, &view);

	//�g�|���W�[�ݒ�
	list.lock()->GetList()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�`��
	list.lock()->GetList()->DrawInstanced(vertex.size(), 1, 0, 0);
}

// �z��̃��Z�b�g
void Box::Reset(void)
{
	vertex.clear();
	vertex.shrink_to_fit();
}
