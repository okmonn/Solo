#include "Mouse.h"
#include "DxLib.h"

// コンストラクタ
Mouse::Mouse() : 
	pos(0), state(0), old_state(0)
{
}

// デストラクタ
Mouse::~Mouse()
{
}

// 処理
void Mouse::UpData(void)
{
	old_state = state;
	state = (GetMouseInput() & MOUSE_INPUT_LEFT);

	GetMousePoint(&pos.x, &pos.y);
}
