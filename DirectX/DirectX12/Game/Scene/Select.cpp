#include "Select.h"
#include "../Game.h"
#include "../../Func.h"
using namespace func;

// コンストラクタ
Select::Select()
{
	fileName.clear();
	func = (GetMidiDevNum() == 0) ? &Select::Key : &Select::Midi;

	std::vector<std::string>m = GetDirFile(".");
}

// デストラクタ
Select::~Select()
{
}

// 描画
void Select::Draw(void)
{
}

// キー入力
void Select::Key(void)
{
}

// MIDI入力
void Select::Midi(void)
{
}

// 処理
void Select::UpData(void)
{
	(this->*func)();
}

