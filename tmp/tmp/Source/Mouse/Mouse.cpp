#include "Mouse.h"
#include "DxLib.h"

// �R���X�g���N�^
Mouse::Mouse() : 
	pos(0), state(0), old_state(0)
{
}

// �f�X�g���N�^
Mouse::~Mouse()
{
}

// ����
void Mouse::UpData(void)
{
	old_state = state;
	state = (GetMouseInput() & MOUSE_INPUT_LEFT);

	GetMousePoint(&pos.x, &pos.y);
}
