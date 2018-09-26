#include "Select.h"
#include "Quest.h"
#include "../Play/Play.h"
#include "../../Game/Game.h"
#include "../../Mouse/Mouse.h"
#include "DxLib.h"
#include <iostream>

// コンストラクタ
Select::Select() :
	mouse(Mouse::Get())
{
	quest.resize(QUESTNAME_MAX);

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
}

// 処理
void Select::UpData(void)
{
	for (int i = 0; i < QUESTNAME_MAX; ++i)
	{
		if ((quest[i].pos.x - quest[i].offset.x <= mouse.GetPos().x && mouse.GetPos().x <= quest[i].pos.x - quest[i].offset.x + quest[i].size.x)
		 && (quest[i].pos.y - quest[i].offset.y <= mouse.GetPos().y && mouse.GetPos().y <= quest[i].pos.y - quest[i].offset.y + quest[i].size.y))
		{
			quest[i].color = GetColor(255, 0, 0);
			if (mouse.TrigerClick() == true)
			{
				game.ChangeScene(new Play());
			}
		}
		else
		{
			quest[i].color = GetColor(255, 255, 255);
		}
	}
}
