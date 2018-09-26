#include "Input.h"
#include "DxLib.h"

// コンストラクタ
Input::Input() : 
	state(0), old_state(0)
{
}

// デストラクタ
Input::~Input()
{
}

// 処理
void Input::UpData(void)
{
	old_state = state;
	state = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
