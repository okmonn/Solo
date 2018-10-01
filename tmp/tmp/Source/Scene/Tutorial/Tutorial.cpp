#include "Tutorial.h"
#include "../Select/Select.h"
#include "../../Charactor/Obj.h"
#include "../../Game/Game.h"
#include "../../GameMane/GameMane.h"
#include "../../Stage/Stage.h"
#include "../../Mouse/Mouse.h"
#include "../../BackGround/BackGround.h"
#include "DxLib.h"

// �^�[�Q�b�g�摜�̃I�t�Z�b�g
#define TARGET_OFFSET 15

// �z�u�ő吔
#define ARRANGEMENT 3

// �R���X�g���N�^
Tutorial::Tutorial() : 
	cnt(0)
{
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

// �f�X�g���N�^
Tutorial::~Tutorial()
{
}

// �v���C���[�̓ǂݍ���
void Tutorial::LoadPlayer(void)
{
	for (unsigned int i = 0; i < ARRANGEMENT; ++i)
	{
		mane.SetID_PL(i, mane.GetID(i));
	}
}

// �`��
void Tutorial::Draw(void)
{
	back->Draw();

	(this->*draw)();

	if (draw == &Tutorial::ButtleDraw)
	{
	}
}

// �퓬�O����
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

// ���w�ƓG�w�̐���
void Tutorial::Description1(void)
{
	const int cntMax = 2;

	if (mouse.TrigerClick() == true)
	{
		++cnt;
		if (cnt > cntMax)
		{

		}
	}
}

// ����
void Tutorial::UpData(void)
{
	if (mane.GetPL().size() == 0 || mane.GetEn().size() == 0)
	{
		draw = &Tutorial::EndDraw;
		updata = &Tutorial::EndUpData;
	}

	(this->*updata)();
}
