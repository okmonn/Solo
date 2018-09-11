#include "Title.h"
#include "../../Game/Game.h"
#include "../Select/Select.h"
#include "../../etc/Share.h"
#include "../../../Source/Func/Func.h"
using namespace func;

// �t�F�[�h���x
#define FADE_SPEED 0.01f;

// �R���X�g���N�^
Title::Title() : 
	large(1.5f), flam(0)
{
	draw = &Title::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Title::Key : &Title::Midi;

	Load();
}

// �f�X�g���N�^
Title::~Title()
{
}

// �摜�ǂݍ���
void Title::Load(void)
{
	AddImg("Material/img/TitleName.png", { (float)Game::Get().GetWinSize().x, (float)Game::Get().GetWinSize().y });
}

// �t�F�[�h�C��
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

// �t�F�[�h�A�E�g
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

// �ʏ�`��
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
