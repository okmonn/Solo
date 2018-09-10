#pragma once
#include "KeyData.h"
#include <memory>

// �L�[�ő吔
#define KEY_MAX 256

class Window;

class Input
{
public:
	// �R���X�g���N�^
	Input(std::weak_ptr<Window>win);
	// �f�X�g���N�^
	~Input();

	// �L�[����
	bool CheckKey(UINT index);

	// �g���K�[�̓���
	bool TriggerKey(UINT index);

private:
	// �C���v�b�g�̐���
	HRESULT CreateInput(void);

	// �L�[�f�o�C�X�̐���
	HRESULT CreateKey(void);

	// �L�[�t�H�[�}�b�g�̃Z�b�g
	HRESULT SetKeyFormat(void);

	// �L�[�̋������x���̃Z�b�g
	HRESULT SetKeyCooperative(void);

	// ����
	void Create(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �Q�ƌ���
	HRESULT result;

	// �C���v�b�g
	LPDIRECTINPUT8 input;

	// �C���v�b�g�f�o�C�X
	LPDIRECTINPUTDEVICE8 key;

	// �L�[���
	BYTE keys[KEY_MAX];

	// �O�̃L�[���
	BYTE olds[KEY_MAX];
};
