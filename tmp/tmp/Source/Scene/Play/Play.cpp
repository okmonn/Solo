#include "Play.h"
#include "../Select/Select.h"
#include "../../Charactor/Obj.h"
#include "../../Game/Game.h"
#include "../../GameMane/GameMane.h"
#include "../../Stage/Stage.h"
#include "../../Mouse/Mouse.h"
#include "../../BackGround/BackGround.h"
#include "DxLib.h"

// ターゲット画像のオフセット
#define TARGET_OFFSET 15

// コマンド最大数
#define COMMAND_MAX 4

// コンストラクタ
Play::Play()
{
	mane.Clear();
	LoadEnemy();
	mane.CreateObj();

	Load("Material/img/Target.png", "target", { 150, 150 }, { mane.GetEn(target)->GetPos().x - TARGET_OFFSET, mane.GetEn(target)->GetPos().y - TARGET_OFFSET });
	Load("Material/img/GameStart.png", "start1", { game.GetWinSize().x, game.GetWinSize().y - 100 });
	Load("Material/img/GameStart.png", "start2", { game.GetWinSize().x , 100 }, { 0, game.GetWinSize().y - 100 });

	draw = &Play::SetDraw;
	updata = &Play::SetUpData;
}

// デストラクタ
Play::~Play()
{
}

// 描画
void Play::Draw(void)
{
	back->Draw();

	(this->*draw)();
}

// 戦闘前処理
void Play::SetUpData(void)
{
	++flam;
	if (flam >= 150)
	{
		flam = 0;
		draw = &Play::ButtleDraw;
		updata = &Play::ButtleUpData;
	}

	image["start1"].pos.y -= image["start1"].size.y / 100;
	image["start2"].pos.y += image["start2"].size.y / 100;
}

// 処理
void Play::UpData(void)
{
	if (mane.GetPL().size() == 0 || mane.GetEn().size() == 0)
	{
		draw = &Play::EndDraw;
		updata = &Play::EndUpData;
	}

	(this->*updata)();
}
