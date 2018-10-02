#include "Tutorial.h"
#include "TutorialData.h"
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

// 配置最大数
#define ARRANGEMENT 3

// かっこのオフセット
const Vec2 offset = {12, 35};

// コンストラクタ
Tutorial::Tutorial() : 
	pos({ 170, 365 }), size({310, 100}), cnt(0), flam(0), index(0), num(-1)
{
	st.resize(3);
	mane.Clear();
	LoadEnemy();
	LoadPlayer();
	mane.CreateObj();

	Load("Material/img/Target.png", "target", { 150, 150 }, { mane.GetEn(target)->GetPos().x - TARGET_OFFSET, mane.GetEn(target)->GetPos().y - TARGET_OFFSET });
	Load("Material/img/GameStart.png", "start1", { game.GetWinSize().x, game.GetWinSize().y - 100 });
	Load("Material/img/GameStart.png", "start2", { game.GetWinSize().x , 100 }, { 0, game.GetWinSize().y - 100 });

	draw = &Tutorial::SetDraw;
	updata = &Tutorial::SetUpData;
}

// デストラクタ
Tutorial::~Tutorial()
{
}

// プレイヤーの読み込み
void Tutorial::LoadPlayer(void)
{
	for (unsigned int i = 0; i < ARRANGEMENT; ++i)
	{
		mane.SetID_PL(i, mane.GetID(i));
	}
}

// 説明文字の表示
void Tutorial::DrawString(const std::string & mozi)
{
	if (mozi.size() > MOZI_MAX * 2 * MAX || cnt >= m.size())
	{
		return;
	}

	++flam;
	if (flam % 10 == 0)
	{
		index = (index + 2 > (int)mozi.size()) ? index : index + 2;
		if ((index - 2) % (MOZI_MAX * 2) == 0)
		{
			++num;
		}
		st[num] = mozi.substr((MOZI_MAX * 2) * num, index - (MOZI_MAX * 2 * num));
	}

	for (unsigned int i = 0; i < st.size(); ++i)
	{
		if (st[i].empty() == true)
		{
			continue;
		}

		DxLib::DrawString(pos.x, pos.y + 32 * i, st[i].c_str(), GetColor(0, 0, 0));
	}
}

// 描画
void Tutorial::Draw(void)
{
	back->Draw();

	(this->*draw)();

	if (draw == &Tutorial::ButtleDraw && cnt < par.size())
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 124);
		DrawBox(par[cnt].left.x, par[cnt].left.y, par[cnt].right.x, par[cnt].right.y, GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DxLib::DrawString(par[cnt].left.x - 1, par[cnt].left.y - 5, "「", GetColor(255, 0, 0));
		DxLib::DrawString(par[cnt].right.x - offset.x, par[cnt].right.y - offset.y, "」", GetColor(255, 0, 0));

		DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, GetColor(255, 255, 255), true);
		DrawString(m[cnt]);
	}
}

// 戦闘前処理
void Tutorial::SetUpData(void)
{
	++flam;
	if (flam >= 150)
	{
		flam = 0;
		draw = &Tutorial::ButtleDraw;
		updata = &Tutorial::Description1;
	}

	image["start1"].pos.y -= image["start1"].size.y / 100;
	image["start2"].pos.y += image["start2"].size.y / 100;
}

// 自陣と敵陣の説明
void Tutorial::Description1(void)
{
	if (mouse.TrigerClick() == true)
	{
		++cnt;
		num   = -1;
		index = 0;
		flam  = 0;
		for (unsigned int i = 0; i < st.size(); ++i)
		{
			st[i].clear();
		}
		if (cnt >= par.size())
		{
			updata = &Tutorial::ButtleUpData;
		}
	}
}

// 処理
void Tutorial::UpData(void)
{
	if (mane.GetPL().size() == 0 || mane.GetEn().size() == 0)
	{
		draw = &Tutorial::EndDraw;
		updata = &Tutorial::EndUpData;
	}

	(this->*updata)();

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos.x += 1;
		printf("%d, %d\n", pos.x, pos.y);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos.x -= 1;
		printf("%d, %d\n", pos.x, pos.y);
	}
	else if (CheckHitKey(KEY_INPUT_UP))
	{
		pos.y -= 1;
		printf("%d, %d\n", pos.x, pos.y);
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos.y += 1;
		printf("%d, %d\n", pos.x, pos.y);
	}
}
