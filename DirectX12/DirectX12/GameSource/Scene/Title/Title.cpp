#include "Title.h"
#include "../../Game/Game.h"
#include "../Select/Select.h"
#include "../../etc/Share.h"
#include "../../../Source/Func/Func.h"
using namespace func;

// フェード速度
#define FADE_SPEED 0.01f;

// コンストラクタ
Title::Title() : 
	large(1.5f), flam(0)
{
	draw = &Title::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Title::Key : &Title::Midi;

	Load();
}

// デストラクタ
Title::~Title()
{
}

// 画像読み込み
void Title::Load(void)
{
	AddImg("Material/img/TitleName.png", { (float)Game::Get().GetWinSize().x, (float)Game::Get().GetWinSize().y });
}

// フェードイン
void Title::FadeIn(void)
{
	alpha += FADE_SPEED;

	SetAlpha(alpha);
	Scene::Draw("TitleName", large);

	if (alpha >= 1.0f)
	{
		alpha = 1.0f;
		draw = &Title::NormalDraw;
	}
	else
	{
		SetAlpha(1.0f);
	}
}

// フェードアウト
void Title::FadeOut(void)
{
	alpha -= FADE_SPEED;

	SetAlpha(alpha);
	Scene::Draw("TitleName", large);

	if (alpha <= 0.0f)
	{
		Game::Get().ChangeScene(new Select());
	}
	else
	{
		SetAlpha(1.0f);
	}
}

// 通常描画
void Title::NormalDraw(void)
{
	Scene::Draw("TitleName", large);
	if (flam >= 20)
	{
		large = (large > 1.0f) ? 0.5f : 1.5f;
		flam = 0;
	}
	++flam;
}

// 描画
void Title::Draw(void)
{
	(this->*draw)();
}

// キー入力
void Title::Key(void)
{
	if (TriggerKey(INPUT_RETURN))
	{
		draw = &Title::FadeOut;
	}
}

// MIDI入力
void Title::Midi(void)
{
	if (GetMidiState() >> 4 == 0x9)
	{
		draw = &Title::FadeOut;
	}
}

// 処理
void Title::UpData(void)
{
	if (alpha < 1.0f)
	{
		return;
	}

	(this->*updata)();
}
