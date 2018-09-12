#include "Select.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
#include <random>
#include <ctime>
#include <functional>
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
	Delete("QuarterNote2");
}

// 読み込み
void Select::Load(void)
{
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f });
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f });
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f });
}

// フェードイン
void Select::FadeIn(void)
{
	alpha += FADE_SPEED;

	SetAlpha(alpha);
	
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
	SetAlpha(alpha);
	Scene::Draw("QuarterNote");
	Scene::Draw("QuarterNote1");
	Scene::Draw("QuarterNote2");
	SetAlpha(1.0f);
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

// メルセンヌツイスタ
void Select::MT(Vec2f & pos, const Vec2f& offset)
{
	std::random_device device;
	auto x = std::bind(std::uniform_int_distribution<float>(0.0f, (float)(Game::Get().GetWinSize().x - offset.x)), std::mt19937(device()));
	auto y = std::bind(std::uniform_int_distribution<float>(0.0f, (float)(Game::Get().GetWinSize().y - offset.y)), std::mt19937(device()));
	pos.x = x();
	pos.y = y();
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

