#include "Title.h"
#include "../../Game/Game.h"
#include "../Select/Select.h"
#include "../../etc/Share.h"
#include "../../../Source/Func/Func.h"
using namespace func;

// コンストラクタ
Title::Title()
{
	func = (GetMidiDevNum() <= 0) ? &Title::Key : &Title::Midi;

	Load();
}

// デストラクタ
Title::~Title()
{
}

// 画像読み込み
void Title::Load(void)
{
	AddImg("Material/img/TitleName.png");
}

// 描画
void Title::Draw(void)
{
	Scene::Draw("TitleName", { 0.0f, 0.0f }, { (float)Game::Get().GetWinSize().x, (float)Game::Get().GetWinSize().y });

	static float alpha = 1.0f;
	SetAlpha(alpha);
	DrawBox(0, 0, 640, 480, 0, 0, 0);
	SetAlpha(1.0f);

	alpha -= 0.005f;
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
