#pragma once

// ���[���^�C�v
enum LaneType {
	TYPE_A,
	TYPE_B,
	TYPE_C,
	TYPE_D,
	TYPE_MAX
};

// �m�[�c���
struct Notes {
	//���[���^�C�v
	LaneType type;
	//�J�n�t���[��
	int start;
	//����
	int time;
};
