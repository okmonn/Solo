#include "Select.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
using namespace func;

// コンストラクタ
Select::Select()
{
	fileName.clear();
	func = (GetMidiDevNum() <= 0) ? &Select::Key : &Select::Midi;

	std::vector<std::wstring>m = GetDirFile(L".");
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

