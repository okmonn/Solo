#include "Select.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
using namespace func;

// コンストラクタ
Select::Select()
{
	fileName.clear();

	draw = &Select::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Select::Key : &Select::Midi;

	Load();
}

// デストラクタ
Select::~Select()
{
	Delete("QuarterNote");
	Delete("QuarterNote1");
}

// 読み込み
void Select::Load(void)
{
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f });
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f }, { 300.0f, 200.0f });
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f }, { 500.0f, 200.0f });
}

// フェードイン
void Select::FadeIn(void)
{
	alpha += FADE_SPEED;

	SetAlpha(alpha);
	Scene::Draw("QuarterNote");
	Scene::Draw("QuarterNote1");
	Scene::Draw("QuarterNote2");

	if (alpha >= 1.0f)
	{
		alpha = 1.0f;
		draw = &Select::NormalDraw;
	}
	else
	{
		SetAlpha(1.0f);
	}
}

// フェードアウト
void Select::FadeOut(void)
{
}

// 通常描画
void Select::NormalDraw(void)
{
	Scene::Draw("QuarterNote");
	Scene::Draw("QuarterNote1");
}

// 描画
void Select::Draw(void)
{
	(this->*draw)();
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
	if (alpha < 1.0f)
	{
		return;
	}

	(this->*updata)();
}

