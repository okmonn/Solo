#pragma once

// �ړ�����
enum class DIR {
	non,
	up,
	down,
	right,
	left
};

// �L�����̏��
enum class State {
	go,         //�O�i
	attack1,    //�˂�
	escape,     //���S
	wait,       //�ҋ@
	attack2,    //�U��
	win,        //����
	masicSet,   //�r���ҋ@
	tool,       //����
	pinch,      //�m��
	gurd,       //�h��
	skill,      //�X�L��
	abnormality,//��Ԉُ�
	damage,     //�_���[�W
	masic,      //���@
	sleep,      //����
	avoid,      //���
	item,       //�A�C�e��
	die         //���S
};

// �X�e�[�^�X�̍ő吔
#define STATE_MAX 18
