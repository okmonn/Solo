#include "Select.h"
#include "Quest.h"
#include "../Choose/Choose.h"
#include "../../Game/Game.h"
#include "../../Mouse/Mouse.h"
#include "../../Stage/Stage.h"
#include "DxLib.h"
#include <iostream>

// �R���X�g���N�^
Select::Select() :
	mouse(Mouse::Get()), stage(Stage::Get())
{
	quest.resize(QUESTNAME_MAX);

	LoadInit();
	QuestInit();
}

// �f�X�g���N�^
Select::~Select()
{
}

// �摜�̓ǂݍ���
void Select::LoadInit(void)
{
	Load("Material/img/1087010201.png", "��t��1", { 250, game.GetWinSize().y });
	Load("Material/img/1105010201.png", "��t��2", { 300, game.GetWinSize().y }, { 350, 0 });
}

// �N�G�X�g���̏�����
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

// �`��
void Select::Draw(void)
{
	Scene::DrawModiGraph("��t��1");
	Scene::DrawModiGraph("��t��2");

	for (int i = 0; i < QUESTNAME_MAX; ++i)
	{
		DrawString(quest[i].pos.x, quest[i].pos.y, quest[i].name.c_str(), quest[i].color, false);
	}
}

// ����
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
				stage.SetIndex(i);
				stage.LoadStage();
				game.ChangeScene(new Choose());
			}
		}
		else
		{
			quest[i].color = GetColor(255, 255, 255);
		}
	}
}
