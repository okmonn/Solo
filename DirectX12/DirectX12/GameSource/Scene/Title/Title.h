#pragma once
#include "../Scene.h"

class Title :
	public Scene
{
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
	// �摜�ǂݍ���
	void Load(void);

	// �t�F�[�h�C��
	void FadeIn(void);

	// �t�F�[�h�A�E�g
	void FadeOut(void);

	// �ʏ�`��
	void NormalDraw(void);

	// �L�[����
	void Key(void);

	// MIDI����
	void Midi(void);


	// �֐��|�C���^
	void (Title::*draw)(void);
	void (Title::*updata)(void);
};

