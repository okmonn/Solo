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

	// �L�[����
	void Key(void);

	// MIDI����
	void Midi(void);


	// �֐��|�C���^
	void (Title::*func)(void);
};

