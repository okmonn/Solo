#pragma once
#include <DirectXMath.h>

// �~����
#define PI 3.14159265359f

// ���W�A���ϊ�
#define RAD(X) (X) * PI / 180.0f

// ���_
struct Vertex {
	//���W
	DirectX::XMFLOAT3 pos;
	//UV
	DirectX::XMFLOAT2 uv;
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
};
