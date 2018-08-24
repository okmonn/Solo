#include "Window.h"
#include "../Icon/Icon.h"
#include <tchar.h>

// �R���X�g���N�^
Window::Window(UINT x, UINT y) : 
	x(x), y(y), handle(nullptr)
{
	window = {};
	rect = {};

	SetWindow();
	SetRect();
	Create();
}

// �f�X�g���N�^
Window::~Window()
{
	//�E�B���h�E�N���X�̏���,�������̉��
	UnregisterClass(window.lpszClassName, window.hInstance);
}

// �E�B���h�E�v���V�[�W��
LRESULT Window::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//�E�B���h�E���j�����ꂽ�Ƃ�
	if (msg == WM_DESTROY)
	{
		//OS�ɑ΂��ăA�v���P�[�V�����I����`����
		PostQuitMessage(0);
		return 0;
	}

	//�K��̏������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

// �E�B���h�E�v�f�̃Z�b�g
void Window::SetWindow(void)
{
	window.cbClsExtra    = 0;
	window.cbSize        = sizeof(WNDCLASSEX);
	window.cbWndExtra    = 0;
	window.hbrBackground = CreateSolidBrush(0x000000);
	window.hCursor       = LoadCursor(NULL, IDC_ARROW);
	window.hIcon         = LoadIcon(NULL, MAKEINTRESOURCE(ICON_ID));
	window.hIconSm       = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(ICON_ID));
	window.hInstance     = GetModuleHandle(0);
	window.lpfnWndProc   = (WNDPROC)WindowProcedure;
	window.lpszClassName = _T("DirectX12");
	window.lpszMenuName  = _T("DirectX12");
	window.style         = CS_HREDRAW | CS_VREDRAW;

	// �E�B���h�E�̓o�^
	RegisterClassEx(&window);
}

// �E�B���h�E�T�C�Y�̃Z�b�g
void Window::SetRect(void)
{
	rect.bottom = y;
	rect.left   = 0;
	rect.right  = x;
	rect.top    = 0;

	// �T�C�Y�̕␳
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
}

// �E�B���h�E�̐���
void Window::Create(void)
{
	handle = CreateWindow(window.lpszClassName, _T("��������"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		(rect.right - rect.left), (rect.bottom - rect.top), nullptr, nullptr, window.hInstance, nullptr);

	//�\�����������E�B���h�E�n���h��,�\���̎w��(SW_����Ȃ��`�g�p)
	ShowWindow(handle, SW_SHOW);
}
