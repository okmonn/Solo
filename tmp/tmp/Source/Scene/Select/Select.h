#pragma once
#include "../Scene.h"
#include <vector>

class Mouse;

class Select :
	public Scene
{
	// �N�G�X�g���ڏ��
	struct QuestName {
		//�N�G�X�g��
		std::string name;
		//���W
		Vec2 pos;
		//�T�C�Y
		Vec2 size;
		//�I�t�Z�b�g
		Vec2 offset;
		//�F
		unsigned int color;
	};

public:
	// �R���X�g���N�^
	Select();
	// �f�X�g���N�^
	~Select();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �摜�̓ǂݍ���
	void LoadInit(void);

	// �N�G�X�g���̏�����
	void QuestInit(void);


	// �}�E�X
	Mouse& mouse;

	// �N�G�X�g����
	std::vector<QuestName>quest;
};
