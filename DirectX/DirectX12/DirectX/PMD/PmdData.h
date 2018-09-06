#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <vector>
#include <map>

// ���_�o�b�t�@
struct VertexData {
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW view;
	//���\�[�X
	ID3D12Resource* resource;
	//���M�f�[�^
	UINT* data;
};

// ���_�C���f�b�N�X
struct VertexIndex {
	//���_�C���f�b�N�X�r���[
	D3D12_INDEX_BUFFER_VIEW view;
	//���\�[�X
	ID3D12Resource* resource;
	//���M�f�[�^
	UINT* data;
};

// �萔�o�b�t�@
struct Con {
	//�q�[�v
	ID3D12DescriptorHeap* heap;
	//���\�[�X
	ID3D12Resource* resource;
	//���M�f�[�^
	UINT8* data;
};

#pragma pack(1)
// �w�b�_�[
struct Header {
	//�^�C�v
	UCHAR type[3];
	//�o�[�W���� 
	FLOAT ver;
	//���O
	UCHAR name[20];
	//�R�����g
	UCHAR comment[256];
	//���_��
	UINT vertexNum;
};
#pragma pack()

// ���_�f�[�^
struct PmdVertex {
	//���W
	DirectX::XMFLOAT3 pos;
	//�@��
	DirectX::XMFLOAT3 normal;
	//UV
	DirectX::XMFLOAT2 uv;
	//�{�[���ԍ�
	USHORT bornNo[2];
	//�E�F�C�g
	UCHAR weight;
	//�֊s���t���O
	UCHAR edge;
};

#pragma pack(1)
// �}�e���A��
struct Material {
	//��{�F
	DirectX::XMFLOAT3 diffuse;
	//�����x
	FLOAT alpha;
	//���ˋ��x
	FLOAT specularity;
	//���ːF
	DirectX::XMFLOAT3 specula;
	//���F
	DirectX::XMFLOAT3 mirror;
	//�g�D�[���ԍ�
	UCHAR toonIndex;
	//�֊s���t���O
	UCHAR edge;
	//�C���f�b�N�X��
	UINT indexNum;
	//�e�N�X�`���p�X
	CHAR texPath[20];
};
#pragma pack()

// �{�[��
struct Born {
	//���O
	CHAR name[20];
	//�e�{�[���ԍ�
	WORD pIndex;
	//�q�{�[���ԍ�
	WORD cIndex;
	//�^�C�v
	BYTE type;
	//IK�e�{�[���ԍ�
	WORD IKpIndex;
	//���W
	DirectX::XMFLOAT3 pos;
};

// �{�[�����W
struct BornPos {
	//�擪���W
	DirectX::XMFLOAT3 head;
	//�������W
	DirectX::XMFLOAT3 tail;
};

// ���f���f�[�^
struct Model {
	//���_�o�b�t�@
	VertexData v;
	//���_�C���f�b�N�X
	VertexIndex i;
	//�萔�o�b�t�@
	Con c;

	//�w�b�_�[
	Header header;
	//���_�f�[�^
	std::vector<PmdVertex>vertex;
	//���_�C���f�b�N�X
	std::vector<USHORT>index;
	//�}�e���A��
	std::vector<Material>material;
	//�{�[��
	std::vector<Born>born;
	//�{�[���m�[�h
	std::vector<std::vector<USHORT>>node;
	//�{�[�����W
	std::vector<BornPos>pos;
	//�e�N�X�`���A�h���X
	std::map<UINT, UINT>id;
};
