#pragma once
#include <Windows.h>

class Window
{
public:
	// �R���X�g���N�^
	Window(UINT x, UINT y);
	// �f�X�g���N�^
	~Window();

	// �E�B���h�E�̐���
	void Create(void);

	// �E�B���h�E�n���h���̎擾
	HWND GetHandle(void) const {
		return handle;
	}

	// X�T�C�Y�̎擾
	UINT GetX(void) const {
		return x;
	}
	// Y�T�C�Y�̎擾
	UINT GetY(void) const {
		return y;
	}

private:
	// �E�B���h�E�v���V�[�W��
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	// �E�B���h�E�v�f�̃Z�b�g
	void SetWindow(void);

	// �E�B���h�E�T�C�Y�̃Z�b�g
	void SetRect(void);


	// �E�B���h�E�n���h��
	HWND handle;

	//  �E�B���h�E
	WNDCLASSEX window;

	// �T�C�Y
	RECT rect;

	// X�T�C�Y
	UINT x;

	// Y�T�C�Y
	UINT y;
};

