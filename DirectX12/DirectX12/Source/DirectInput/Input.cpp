#include "Input.h"
#include "../Window/Window.h"
#include <tchar.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// �����[�X�}�N��
#define Release(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }

// �R���X�g���N�^
Input::Input(std::weak_ptr<Window>win) :
	win(win), result(S_OK), input(nullptr), key(nullptr)
{
	memset(&keys, 0, sizeof(keys));
	memset(&olds, 0, sizeof(olds));

	Create();
}

// �f�X�g���N�^
Input::~Input()
{
	Release(key);
	Release(input);
}

// �C���v�b�g�̐���
HRESULT Input::CreateInput(void)
{
	result = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(&input), NULL);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�C���v�b�g�̐����F���s\n"));
	}

	return result;
}

// �L�[�f�o�C�X�̐���
HRESULT Input::CreateKey(void)
{
	result = input->CreateDevice(GUID_SysKeyboard, &key, NULL);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�L�[�f�o�C�X�̐����F���s\n"));
	}

	return result;
}

// �L�[�t�H�[�}�b�g�̃Z�b�g
HRESULT Input::SetKeyFormat(void)
{
	result = key->SetDataFormat(&keybord);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�L�[�t�H�[�}�b�g�̃Z�b�g�F���s\n"));
	}

	return result;
}

// �L�[�̋������x���̃Z�b�g
HRESULT Input::SetKeyCooperative(void)
{
	result = key->SetCooperativeLevel(win.lock()->GetHandle(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�L�[�̋������x���̃Z�b�g�F���s\n"));
		return result;
	}

	//���̓f�o�C�X�ւ̃A�N�Z�X�������擾
	key->Acquire();

	return result;
}

// ����
void Input::Create(void)
{
	CreateInput();
	CreateKey();
	SetKeyFormat();
	SetKeyCooperative();
}

// �L�[����
bool Input::CheckKey(UINT index)
{
	//�_�~�[�錾
	bool flag = false;

	//�L�[�����擾
	key->GetDeviceState(sizeof(keys), &keys);

	if (keys[index] & 0x80)
	{
		flag = true;
	}

	olds[index] = keys[index];

	return flag;
}

// �g���K�[�̓���
bool Input::TriggerKey(UINT index)
{
	//�_�~�[�錾
	bool flag = false;

	//�L�[�����擾
	key->GetDeviceState(sizeof(keys), &keys);

	if ((keys[index] & 0x80) && !(olds[index] & 0x80))
	{
		flag = true;
	}

	olds[index] = keys[index];

	return flag;
}
