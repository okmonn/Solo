#pragma once
#include "../Scene.h"
#include <vector>
#include <string>

class Select :
	public Scene
{
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
	// �ǂݍ���
	void Load(void);

	// �����Z���k�c�C�X�^
	void MT(Vec2f& pos, const Vec2f& offset = 0.0f);
	void MT(unsigned int& i, unsigned int min, unsigned int max);

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


	// �y�Ȉꗗ
	std::vector<std::string> song;

	// �`�搔
	unsigned int drawCnt;

	// ���߃t���O
	bool flag;

	// ���݂̃C���f�b�N�X
	int index;

	// �֐��|�C���^
	void (Select::*draw)(void);
	void (Select::*updata)(void);
};

