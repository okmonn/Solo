#include "Select.h"
#include "Quest.h"
#include "../Choose/Choose.h"
#include "../Tutorial/Tutorial.h"
#include "../../Game/Game.h"
#include "../../Mouse/Mouse.h"
#include "../../Stage/Stage.h"
#include "DxLib.h"
#include <iostream>

// コンストラクタ
Select::Select() :
	mouse(Mouse::Get()), stage(Stage::Get()), color(0)
{
	quest.resize(QUESTNAME_MAX);

	func = &Select::FadeIn;

	LoadInit();
	QuestInit();
}

// デストラクタ
Select::~Select()
{
}

// 画像の読み込み
void Select::LoadInit(void)
{
	Load("Material/img/1087010201.png", "受付嬢1", { 250, game.GetWinSize().y });
	Load("Material/img/1105010201.png", "受付嬢2", { 300, game.GetWinSize().y }, { 350, 0 });
}

// クエスト名の初期化
void Select::QuestInit(void)
{
	for (unsigned int i = 0; i < quest.size(); ++i)
	{
		quest[i].name   = questName[i];
		quest[i].pos    = { game.GetWinSize().x / 2 - 80, game.GetWinSize().y / 2 + 30 - 100 * (int)i };
		quest[i].size   = { 170, 60 };
		quest[i].offset = { 10, 10 };
		quest[i].color  = GetColor(255, 255, 255);
	}
}

// 描画
void Select::Draw(void)
{
	Scene::DrawModiGraph("受付嬢1");
	Scene::DrawModiGraph("受付嬢2");

	for (int i = 0; i < QUESTNAME_MAX; ++i)
	{
		DrawString(quest[i].pos.x, quest[i].pos.y, quest[i].name.c_str(), quest[i].color, false);
	}

	if (alpha > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, game.GetWinSize().x, game.GetWinSize().y, color, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// フェードイン
void Select::FadeIn(void)
{
	alpha -= fadeSpeed;
	if (alpha <= 0)
	{
		alpha = 0;
		func = &Select::Normal;
	}
}

// 通常処理
void Select::Normal(void)
{
	for (int i = 0; i < QUESTNAME_MAX; ++i)
	{
		if ((quest[i].pos.x - quest[i].offset.x <= mouse.GetPos().x && mouse.GetPos().x <= quest[i].pos.x - quest[i].offset.x + quest[i].size.x)
			&& (quest[i].pos.y - quest[i].offset.y <= mouse.GetPos().y && mouse.GetPos().y <= quest[i].pos.y - quest[i].offset.y + quest[i].size.y))
		{
			quest[i].color = GetColor(255, 0, 0);
			if (mouse.TrigerClick() == true)
			{
				stage.SetIndex(i);
				stage.LoadStage();

				color = (stage.GetIndex() != 0) ? 0 : GetColor(255, 255, 255);
				
				func = &Select::FadeOut;

				break;
			}
		}
		else
		{
			quest[i].color = GetColor(255, 255, 255);
		}
	}
}

// フェードアウト
void Select::FadeOut(void)
{
	alpha += fadeSpeed;
	if (alpha >= 255)
	{
		if (stage.GetIndex() != 0)
		{
			game.ChangeScene(new Choose());
		}
		else
		{
			game.ChangeScene(new Tutorial());
		}
	}
}


// 処理
void Select::UpData(void)
{
	(this->*func)();
}
