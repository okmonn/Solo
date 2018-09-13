#include "Select.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
#include <random>
#include <functional>
#include <sstream>
using namespace func;

#define QuarterNote_MAX 3

// コンストラクタ
Select::Select() :
	flag(false)
{
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
	for (UINT i = 0; i < QuarterNote_MAX; ++i)
	{
		std::ostringstream st;
		if (i != 0)
		{
			st << i << std::flush;
		}
		AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f });
		MT(data["QuarterNote" + st.str()].pos, data["QuarterNote" + st.str()].size);
		st.str("");
	}
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
	for (UINT i = 0; i < QuarterNote_MAX; ++i)
	{
		std::ostringstream st;
		if (i != 0)
		{
			st << i << std::flush;
		}
		Scene::Draw("QuarterNote" + st.str());
		st.str("");
	}
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
	auto x = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().x - (UINT)offset.x)), std::mt19937(device()));
	auto y = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().y - (UINT)offset.y)), std::mt19937(device()));
	pos.x = static_cast<float>(x());
	pos.y = static_cast<float>(y());
}

// 処理
void Select::UpData(void)
{
	(this->*updata)();

	if (flag == false && alpha < 2.0f)
	{
		alpha += FADE_SPEED;
		if (alpha >= 2.0f)
		{
			alpha = 1.0f;
			flag = true;
		}
	}
	else if (flag == true && alpha > -1.0f)
	{
		alpha -= FADE_SPEED;
		if (alpha <= -1.0f)
		{
			MT(data["QuarterNote"].pos, data["QuarterNote"].size);
			MT(data["QuarterNote1"].pos, data["QuarterNote1"].size);
			MT(data["QuarterNote2"].pos, data["QuarterNote2"].size);
			alpha = 0.0f;
			flag = false;
		}
	}
}

