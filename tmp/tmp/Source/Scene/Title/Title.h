#pragma once
#include "../Scene.h"
#include <vector>

class Mouse;

class Title :
	public Scene
{
	struct Circle {
		//���W
		Vec2 pos;
		//���a
		int radius;
		//�F
		unsigned int color;
		//�o���t���O
		bool flag;
	};

public:
	// �R���X�g���N�^
	Title();
	// �f�X�g���N�^
	~Title();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �~�̏�����
	void CircleInit(void);

	// �t�F�[�h�C��
	void FadeIn(void);

	// �ʏ폈��
	void Normal(void);

	// �t�F�[�h�A�E�g
	void FadeOut(void);


	// �}�E�X
	Mouse& mouse;

	// �~
	std::vector<Circle>circle;

	// �֐��|�C���^
	void (Title::*func)(void);
};

