#include "Title.h"
#include "../Game.h"
#include "Select.h"
#include "../../Func.h"
using namespace func;

// コンストラクタ
Title::Title()
{
	func = (GetMidiDevNum() == 0) ? &Title::Key : &Title::Midi;
}

// デストラクタ
Title::~Title()
{
}

// 描画
void Title::Draw(void)
{
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
}
