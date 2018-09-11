#include "Texture.h"
#include "WICTextureLoader12.h"
#include "../Device/Device.h"
#include "../Command/List/List.h"
#include "../RootSignature/Root.h"
#include "../PipeLine/Pipe.h"
#include "../Descriptor/ConstantBuffer/Constant.h"
#include <tchar.h>

// ���_�̍ő吔
#define VERTEX_MAX 4

// �R���X�g���N�^
Texture::Texture(std::weak_ptr<Device>dev, std::weak_ptr<List>list, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe, std::weak_ptr<Constant>con) :
	root(root), pipe(pipe), con(con)
{
	this->dev = dev;
	this->list = list;

	wic.clear();

	//WIC�̏�������
	CoInitialize(nullptr);
}

// �f�X�g���N�^
Texture::~Texture()
{
	for (auto itr = wic.begin(); itr != wic.end(); ++itr)
	{
		itr->second.resource->Unmap(0, nullptr);
		itr->second.decode.release();
		Release(itr->second.resource);
		Release(itr->second.con.resource);
		Release(itr->second.con.heap);
	}
}

// WIC�ǂݍ���
HRESULT Texture::LoadWIC(UINT & index, const std::string& fileName)
{
	UINT* n = &index;

	std::wstring path = func::ChangeUnicode(fileName.c_str());

	result = DirectX::LoadWICTextureFromFile(dev.lock()->Get(), path.c_str(), &wic[n].con.resource, wic[n].decode, wic[n].sub);
	if (FAILED(result))
	{
		OutputDebugString(_T("\nWIC�e�N�X�`���̓ǂݍ��݁F���s\n"));
		return result;
	}

	result = CreateHeap(n);
	result = CreateShaderView(n);
	result = CreateResource(n);

	return result;
}

// �萔�o�b�t�@�q�[�v�̐���
HRESULT Texture::CreateHeap(UINT * index)
{
	//�q�[�v�ݒ�p�\���̂̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask       = 0;
	desc.NumDescriptors = 1;
	desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	//�q�[�v����
	result = dev.lock()->Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&wic[index].con.heap));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�e�N�X�`���̒萔�q�[�v�̐����F���s\n"));
	}

	return result;
}

// �V�F�[�_���\�[�X�r���[�̐���
HRESULT Texture::CreateShaderView(UINT * index)
{
	//�V�F�[�_���\�[�X�r���[�ݒ�p�\���̂̐ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format                    = wic[index].con.resource->GetDesc().Format;
	desc.ViewDimension             = D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels       = 1;
	desc.Texture2D.MostDetailedMip = 0;
	desc.Shader4ComponentMapping   = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	//�V�F�[�_�[���\�[�X�r���[�̐���
	dev.lock()->Get()->CreateShaderResourceView(wic[index].con.resource, &desc, wic[index].con.heap->GetCPUDescriptorHandleForHeapStart());

	return result;
}

// ���_���\�[�X�̐���
HRESULT Texture::CreateResource(UINT* index)
{
	//�z��̃������m��
	wic[index].vertex.resize(VERTEX_MAX);

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
	desc.Width            = sizeof(TexVertex) * wic[index].vertex.size();
	desc.Height           = 1;
	desc.DepthOrArraySize = 1;
	desc.MipLevels        = 1;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count = 1;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//���\�[�X����
	result = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&wic[index].resource));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�e�N�X�`���̒��_���\�[�X�̐����F���s\n"));
		return result;
	}

	//���M�͈�
	D3D12_RANGE range = { 0,0 };

	//�}�b�s���O
	result = wic[index].resource->Map(0, &range, reinterpret_cast<void**>(&wic[index].data));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�e�N�X�`���̒��_�}�b�s���O�F���s\n"));
		return result;
	}

	//���_�f�[�^�̃R�s�[
	memcpy(wic[index].data, wic[index].vertex.data(), sizeof(TexVertex) * wic[index].vertex.size());

	//���_�o�b�t�@�ݒ�p�\���̂̐ݒ�
	wic[index].view.BufferLocation = wic[index].resource->GetGPUVirtualAddress();
	wic[index].view.SizeInBytes    = sizeof(TexVertex) * wic[index].vertex.size();
	wic[index].view.StrideInBytes  = sizeof(TexVertex);

	return result;
}

// �`�揀��
HRESULT Texture::SetDraw(UINT & index)
{
	//���\�[�X�ݒ�p�\����
	D3D12_RESOURCE_DESC desc = wic[&index].con.resource->GetDesc();

	//�{�b�N�X�ݒ�p�\���̂̐ݒ�
	D3D12_BOX box = {};
	box.back   = 1;
	box.bottom = desc.Height;
	box.front  = 0;
	box.left   = 0;
	box.right  = static_cast<UINT>(desc.Width);
	box.top    = 0;

	//�T�u���\�[�X�ɏ�������
	result = wic[&index].con.resource->WriteToSubresource(0, &box, wic[&index].decode.get(), wic[&index].sub.RowPitch, wic[&index].sub.SlicePitch);
	if (FAILED(result))
	{
		OutputDebugString(_T("�e�N�X�`���̃T�u���\�[�X�����݁F���s\n"));
		return result;
	}

	SetDescriptor(index);

	return result;
}

// �f�B�X�N���v�^�[�̃Z�b�g
void Texture::SetDescriptor(UINT& index)
{
	//�q�[�v�̃Z�b�g
	list.lock()->GetList()->SetDescriptorHeaps(1, &wic[&index].con.heap);

	//�f�B�X�N���v�^�[�e�[�u���̃Z�b�g
	list.lock()->GetList()->SetGraphicsRootDescriptorTable(1, wic[&index].con.heap->GetGPUDescriptorHandleForHeapStart());
}

// �`��
void Texture::Draw(UINT & index, const Vec2f & pos, float alpha, UINT turnX, UINT turnY)
{
	UINT* n = &index;

	list.lock()->SetRoot(root.lock()->Get());
	list.lock()->SetPipe(pipe.lock()->Get());

	con.lock()->SetConstant();

	//���\�[�X�ݒ�p�\����
	D3D12_RESOURCE_DESC desc = wic[n].con.resource->GetDesc();

	//UV���W
	DirectX::XMFLOAT2 leftUp    = { (static_cast<FLOAT>(desc.Width) * turnX),                                    (static_cast<FLOAT>(desc.Height) * turnY) };
	DirectX::XMFLOAT2 rightUp   = { (static_cast<FLOAT>(desc.Width) - (static_cast<FLOAT>(desc.Width) * turnX)), (static_cast<FLOAT>(desc.Height) * turnY) };
	DirectX::XMFLOAT2 leftDown  = { (static_cast<FLOAT>(desc.Width) * turnX),                                    (static_cast<FLOAT>(desc.Height) - (static_cast<FLOAT>(desc.Height) * turnY)) };
	DirectX::XMFLOAT2 rightDown = { (static_cast<FLOAT>(desc.Width) - (static_cast<FLOAT>(desc.Width) * turnX)), (static_cast<FLOAT>(desc.Height) - (static_cast<FLOAT>(desc.Height) * turnY)) };

	//����
	wic[n].vertex[0] = { { pos.x,                                   pos.y,                                   0.0f }, leftUp,    alpha };
	//�E��
	wic[n].vertex[1] = { { pos.x + static_cast<FLOAT>(desc.Width),  pos.y,                                   0.0f }, rightUp,   alpha };
	//����
	wic[n].vertex[2] = { { pos.x,                                   pos.y + static_cast<FLOAT>(desc.Height), 0.0f }, leftDown,  alpha };
	//�E��
	wic[n].vertex[3] = { { pos.x + static_cast<FLOAT>(desc.Width),  pos.y + static_cast<FLOAT>(desc.Height), 0.0f }, rightDown, alpha };

	//���_�f�[�^�̍X�V
	memcpy(wic[n].data, wic[n].vertex.data(), sizeof(TexVertex) * wic[n].vertex.size());

	//���_�o�b�t�@�r���[�̃Z�b�g
	list.lock()->GetList()->IASetVertexBuffers(0, 1, &wic[n].view);

	//�g�|���W�[�ݒ�
	list.lock()->GetList()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (FAILED(SetDraw(index)))
	{
		return;
	}

	//�`��
	list.lock()->GetList()->DrawInstanced(wic[n].vertex.size(), 1, 0, 0);
}

// �`��E�T�C�Y�w��
void Texture::Draw(UINT & index, const Vec2f & pos, const Vec2f & size, float alpha, UINT turnX, UINT turnY)
{
	UINT* n = &index;

	list.lock()->SetRoot(root.lock()->Get());
	list.lock()->SetPipe(pipe.lock()->Get());

	con.lock()->SetConstant();

	//���\�[�X�ݒ�p�\����
	D3D12_RESOURCE_DESC desc = wic[n].con.resource->GetDesc();

	//UV���W
	DirectX::XMFLOAT2 leftUp    = { (static_cast<FLOAT>(desc.Width) * turnX),                                    (static_cast<FLOAT>(desc.Height) * turnY) };
	DirectX::XMFLOAT2 rightUp   = { (static_cast<FLOAT>(desc.Width) - (static_cast<FLOAT>(desc.Width) * turnX)), (static_cast<FLOAT>(desc.Height) * turnY) };
	DirectX::XMFLOAT2 leftDown  = { (static_cast<FLOAT>(desc.Width) * turnX),                                    (static_cast<FLOAT>(desc.Height) - (static_cast<FLOAT>(desc.Height) * turnY)) };
	DirectX::XMFLOAT2 rightDown = { (static_cast<FLOAT>(desc.Width) - (static_cast<FLOAT>(desc.Width) * turnX)), (static_cast<FLOAT>(desc.Height) - (static_cast<FLOAT>(desc.Height) * turnY)) };

	//����
	wic[n].vertex[0] = { { pos.x,           pos.y,          0.0f }, leftUp,   alpha };
	//�E��
	wic[n].vertex[1] = { { pos.x + size.x,  pos.y,          0.0f }, rightUp,  alpha };
	//����
	wic[n].vertex[2] = { { pos.x,           pos.y + size.y, 0.0f }, leftDown, alpha };
	//�E��
	wic[n].vertex[3] = { { pos.x + size.x,  pos.y + size.y, 0.0f }, rightDown,alpha };

	//���_�f�[�^�̍X�V
	memcpy(wic[n].data, wic[n].vertex.data(), sizeof(TexVertex) * wic[n].vertex.size());

	//���_�o�b�t�@�r���[�̃Z�b�g
	list.lock()->GetList()->IASetVertexBuffers(0, 1, &wic[n].view);

	//�g�|���W�[�ݒ�
	list.lock()->GetList()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (FAILED(SetDraw(index)))
	{
		return;
	}

	//�`��
	list.lock()->GetList()->DrawInstanced(wic[n].vertex.size(), 1, 0, 0);
}

// �`��E�T�C�Y�w��E����
void Texture::Draw(UINT& index, const Vec2f& pos, const Vec2f& size, const Vec2f& rectPos, const Vec2f& rectSize, float alpha, UINT turnX, UINT turnY)
{
	UINT* n = &index;

	list.lock()->SetRoot(root.lock()->Get());
	list.lock()->SetPipe(pipe.lock()->Get());

	con.lock()->SetConstant();

	//���\�[�X�ݒ�p�\����
	D3D12_RESOURCE_DESC desc = wic[n].con.resource->GetDesc();

	//UV���W
	DirectX::XMFLOAT2 leftUp    = { rectPos.x + (rectSize.x * turnX),                rectPos.y + (rectSize.y * turnY) };
	DirectX::XMFLOAT2 rightUp   = { rectPos.x + (rectSize.x - (rectSize.x * turnX)), rectPos.y + (rectSize.y * turnY) };
	DirectX::XMFLOAT2 leftDown  = { rectPos.x + (rectSize.x * turnX),                rectPos.y + (rectSize.y - (rectSize.y * turnY)) };
	DirectX::XMFLOAT2 rightDown = { rectPos.x + (rectSize.x - (rectSize.x * turnX)), rectPos.y + (rectSize.y - (rectSize.y * turnY)) };

	//����
	wic[n].vertex[0] = { { pos.x,           pos.y,          0.0f }, leftUp,    alpha };
	//�E��
	wic[n].vertex[1] = { { pos.x + size.x,  pos.y,          0.0f }, rightUp,   alpha };
	//����
	wic[n].vertex[2] = { { pos.x,           pos.y + size.y, 0.0f }, leftDown,  alpha };
	//�E��
	wic[n].vertex[3] = { { pos.x + size.x,  pos.y + size.y, 0.0f }, rightDown, alpha };

	//���_�f�[�^�̍X�V
	memcpy(wic[n].data, wic[n].vertex.data(), sizeof(TexVertex) * wic[n].vertex.size());

	//���_�o�b�t�@�r���[�̃Z�b�g
	list.lock()->GetList()->IASetVertexBuffers(0, 1, &wic[n].view);

	//�g�|���W�[�ݒ�
	list.lock()->GetList()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (FAILED(SetDraw(index)))
	{
		return;
	}

	//�`��
	list.lock()->GetList()->DrawInstanced(wic[n].vertex.size(), 1, 0, 0);
}

// �`��E���R�ό`
void Texture::FreelyDraw(UINT & index, const Vec2f & pos1, const Vec2f & pos2, const Vec2f & pos3, const Vec2f & pos4, float alpha, UINT turnX, UINT turnY)
{
	UINT* n = &index;

	list.lock()->SetRoot(root.lock()->Get());
	list.lock()->SetPipe(pipe.lock()->Get());

	con.lock()->SetConstant();

	//���\�[�X�ݒ�p�\����
	D3D12_RESOURCE_DESC desc = wic[n].con.resource->GetDesc();

	//UV���W
	DirectX::XMFLOAT2 leftUp    = { (static_cast<FLOAT>(desc.Width) * turnX),                                    (static_cast<FLOAT>(desc.Height) * turnY) };
	DirectX::XMFLOAT2 rightUp   = { (static_cast<FLOAT>(desc.Width) - (static_cast<FLOAT>(desc.Width) * turnX)), (static_cast<FLOAT>(desc.Height) * turnY) };
	DirectX::XMFLOAT2 leftDown  = { (static_cast<FLOAT>(desc.Width) * turnX),                                    (static_cast<FLOAT>(desc.Height) - (static_cast<FLOAT>(desc.Height) * turnY)) };
	DirectX::XMFLOAT2 rightDown = { (static_cast<FLOAT>(desc.Width) - (static_cast<FLOAT>(desc.Width) * turnX)), (static_cast<FLOAT>(desc.Height) - (static_cast<FLOAT>(desc.Height) * turnY)) };

	//����
	wic[n].vertex[0] = { { pos1.x,  pos1.y, 0.0f }, leftUp,   alpha };
	//�E��
	wic[n].vertex[1] = { { pos2.x , pos2.y, 0.0f }, rightUp,  alpha };
	//����
	wic[n].vertex[2] = { { pos3.x,  pos3.y, 0.0f }, leftDown, alpha };
	//�E��
	wic[n].vertex[3] = { { pos4.x,  pos4.y, 0.0f }, rightDown,alpha };

	//���_�f�[�^�̍X�V
	memcpy(wic[n].data, wic[n].vertex.data(), sizeof(TexVertex) * wic[n].vertex.size());

	//���_�o�b�t�@�r���[�̃Z�b�g
	list.lock()->GetList()->IASetVertexBuffers(0, 1, &wic[n].view);

	//�g�|���W�[�ݒ�
	list.lock()->GetList()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (FAILED(SetDraw(index)))
	{
		return;
	}

	//�`��
	list.lock()->GetList()->DrawInstanced(wic[n].vertex.size(), 1, 0, 0);
}

// �`��E�����E���R�ό`
void Texture::FreelyDraw(UINT & index, const Vec2f & rectPos, const Vec2f & rectSize, const Vec2f & pos1, const Vec2f & pos2, const Vec2f & pos3, const Vec2f & pos4, float alpha, UINT turnX, UINT turnY)
{
	UINT* n = &index;

	list.lock()->SetRoot(root.lock()->Get());
	list.lock()->SetPipe(pipe.lock()->Get());

	con.lock()->SetConstant();

	//���\�[�X�ݒ�p�\����
	D3D12_RESOURCE_DESC desc = wic[n].con.resource->GetDesc();

	//UV���W
	DirectX::XMFLOAT2 leftUp    = { rectPos.x + (rectSize.x * turnX),                rectPos.y + (rectSize.y * turnY) };
	DirectX::XMFLOAT2 rightUp   = { rectPos.x + (rectSize.x - (rectSize.x * turnX)), rectPos.y + (rectSize.y * turnY) };
	DirectX::XMFLOAT2 leftDown  = { rectPos.x + (rectSize.x * turnX),                rectPos.y + (rectSize.y - (rectSize.y * turnY)) };
	DirectX::XMFLOAT2 rightDown = { rectPos.x + (rectSize.x - (rectSize.x * turnX)), rectPos.y + (rectSize.y - (rectSize.y * turnY)) };

	//����
	wic[n].vertex[0] = { { pos1.x, pos1.y, 0.0f }, leftUp,    alpha };
	//�E��
	wic[n].vertex[1] = { { pos2.x, pos2.y, 0.0f }, rightUp,   alpha };
	//����
	wic[n].vertex[2] = { { pos3.x, pos3.y, 0.0f }, leftDown,  alpha };
	//�E��
	wic[n].vertex[3] = { { pos4.x, pos4.y, 0.0f }, rightDown, alpha };

	//���_�f�[�^�̍X�V
	memcpy(wic[n].data, wic[n].vertex.data(), sizeof(TexVertex) * wic[n].vertex.size());

	//���_�o�b�t�@�r���[�̃Z�b�g
	list.lock()->GetList()->IASetVertexBuffers(0, 1, &wic[n].view);

	//�g�|���W�[�ݒ�
	list.lock()->GetList()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (FAILED(SetDraw(index)))
	{
		return;
	}

	//�`��
	list.lock()->GetList()->DrawInstanced(wic[n].vertex.size(), 1, 0, 0);
}

// �폜
void Texture::Delete(UINT & index)
{
	if (wic.find(&index) != wic.end())
	{
		if (wic[&index].resource != nullptr)
		{
			wic[&index].resource->Unmap(0, nullptr);
			wic[&index].decode.release();
			Release(wic[&index].resource);
			Release(wic[&index].con.resource);
			Release(wic[&index].con.heap);
		}

		wic.erase(wic.find(&index));
	}
}

// ���j�R�[�h�ϊ�
std::wstring func::ChangeUnicode(const CHAR * str)
{
	//�������̎擾
	auto byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str, -1, nullptr, 0);

	std::wstring wstr;
	wstr.resize(byteSize);

	//�ϊ�
	byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str, -1, &wstr[0], byteSize);

	return wstr;
}