#include "Title.h"
#include "../Game.h"
#include "Select.h"
#include "../etc/Share.h"
#include "../../Func.h"
using namespace func;

// コンストラクタ
Title::Title()
{
	func = (GetMidiDevNum() == 0) ? &Title::Key : &Title::Midi;

	Load();
}

// デストラクタ
Title::~Title()
{
}

// 画像読み込み
void Title::Load(void)
{
	AddImg("Materials/img/TitleName.png");
}

// 描画
void Title::Draw(void)
{
	Scene::Draw("TitleName", { 0.0f, 0.0f }, { (float)Game::Get().GetWinSize().x, (float)Game::Get().GetWinSize().y });
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
