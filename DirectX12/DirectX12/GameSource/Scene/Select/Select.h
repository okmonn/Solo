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


	// �f�B���N�g�����̃t�@�C����
	std::vector<std::string>fileName;

	// �֐��|�C���^
	void (Select::*draw)(void);
	void (Select::*updata)(void);
};

