#pragma once
#include <DirectXMath.h>
#include <string>

// VMD�w�b�_�[
struct VmdHeader {
	//�w�b�_�[
	char header[30];
	//���f����
	char modelName[20];
};

#pragma pack(1)
// ���[�V�����f�[�^
struct VmdMotion {
	//�{�[����
	char bornName[15];
	//�t���[��
	unsigned int flam;
	//�ʒu
	DirectX::XMFLOAT3 pos;
	//�N�H�[�^�j�I��
	DirectX::XMFLOAT4 rotation;
	//�x�W�F�f�[�^
	unsigned char interpolation[64];
};
#pragma pack()

// �f�[�^
struct Motion {
	// �{�[����
	std::string name;
	// �N�H�[�^�j�I��
	DirectX::XMVECTOR quaternion;
};