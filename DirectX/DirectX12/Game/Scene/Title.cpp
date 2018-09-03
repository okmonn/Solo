#include "Title.h"
#include "../Game.h"
#include "Select.h"
#include "../../Func.h"
using namespace func;
#include <stdio.h>

UINT n = 0;
UINT a = 0;

// コンストラクタ
Title::Title()
{
	func = (GetMidiDevNum() == 0) ? &Title::Key : &Title::Midi;
	LoadImg(n, "img/sample.png");
	LoadWave(a, "wave/sample1.wav");
}

// デストラクタ
Title::~Title()
{
}

// 描画
void Title::Draw(void)
{
	func::Draw(n, 0, 0);
}

// キー入力
void Title::Key(void)
{
	if (TriggerKey(INPUT_RETURN))
	{
		Game::Get().ChangeScene(new Select());
	}
}

// MIDI入力
void Title::Midi(void)
{

}

// 処理
void Title::UpData(void)
{
	(this->*func)();
	PlayWave(a);
}
