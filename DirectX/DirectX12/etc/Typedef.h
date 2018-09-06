#pragma once
#include <DirectXMath.h>

// �~����
#define PI 3.14159265359f

// ���W�A���ϊ�
#define RAD(X) (X) * PI / 180.0f

// �|�C���g���_
struct PointVertex {
	//���W
	DirectX::XMFLOAT3 pos;
	//�F
	DirectX::XMFLOAT4 color;
};

// �e�N�X�`�����_
struct TexVertex {
	//���W
	DirectX::XMFLOAT3 pos;
	//UV
	DirectX::XMFLOAT2 uv;
	//���l
	float alpha;
};

// ��ԍs��
struct WVP
{
	//���[���h
	DirectX::XMMATRIX world;
	//�r���[
	DirectX::XMMATRIX view;
	//�v���W�F�N�V����
	DirectX::XMMATRIX projection;
	// �E�B���h�E�T�C�Y
	DirectX::XMFLOAT2 window;
};
