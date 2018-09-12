#include "Title.h"
#include "../../Game/Game.h"
#include "../Select/Select.h"
#include "../../etc/Share.h"
#include "../../../Source/Func/Func.h"
using namespace func;
#include <iostream>

// �R���X�g���N�^
Title::Title() : 
	flam(0)
{
	draw = &Title::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Title::Key : &Title::Midi;

	Load();

	printf("�^�C�g��\n");
}

// �f�X�g���N�^
Title::~Title()
{
	Delete("TitleName");
	Delete("Enter");
	printf("�^�C�g���j��\n");
}

// �摜�ǂݍ���
void Title::Load(void)
{
	AddImg("Material/img/TitleName.png", { (float)Game::Get().GetWinSize().x, (float)Game::Get().GetWinSize().y });
	AddImg("Material/img/Enter.png", { 300.0f, 50.0f }, { (float)Game::Get().GetWinSize().x / 2 - 300.0f / 2, (float)Game::Get().GetWinSize().y / 2 - 50.0f / 2 }, 0.5f);
}

// �t�F�[�h�C��
void Title::FadeIn(void)
{
	alpha += FADE_SPEED;

	SetAlpha(alpha);
	Scene::Draw("TitleName");

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

// �t�F�[�h�A�E�g
void Title::FadeOut(void)
{
	alpha -= FADE_SPEED;

	SetAlpha(alpha);
	Scene::Draw("TitleName");

	if (alpha <= 0.0f)
	{
		Game::Get().ChangeScene(new Select());
	}
	else
	{
		SetAlpha(1.0f);
	}
}

// �ʏ�`��
void Title::NormalDraw(void)
{
	Scene::Draw("TitleName");
	Scene::Draw("Enter");
	if (flam >= 20)
	{
		data["TitleName"].large = (data["TitleName"].large > 1.0f) ? 1.0f : 1.5f;
		flam = 0;
	}
	++flam;
}

// �`��
void Title::Draw(void)
{
	(this->*draw)();
}

// �L�[����
void Title::Key(void)
{
	if (TriggerKey(INPUT_RETURN))
	{
		data["TitleName"].large = 1.0f;
		draw = &Title::FadeOut;
	}
}

// MIDI����
void Title::Midi(void)
{
	if (GetMidiState() >> 4 == 0x9)
	{
		draw = &Title::FadeOut;
	}
}

// ����
void Title::UpData(void)
{
	if (alpha < 1.0f)
	{
		return;
	}

	(this->*updata)();
}
