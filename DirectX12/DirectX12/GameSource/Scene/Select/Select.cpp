#include "Select.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
using namespace func;
#include <iostream>

// �R���X�g���N�^
Select::Select()
{
	fileName.clear();

	draw = &Select::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Select::Key : &Select::Midi;

	Load();

	printf("�Z���N�g\n");
}

// �f�X�g���N�^
Select::~Select()
{
	printf("�Z���N�g�j��\n");
}

// �ǂݍ���
void Select::Load(void)
{
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f });
	AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f }, { 300.0f, 200.0f });
}

// �t�F�[�h�C��
void Select::FadeIn(void)
{
	alpha += FADE_SPEED;

	SetAlpha(alpha);
	Scene::Draw("QuarterNote");
	Scene::Draw("QuarterNote1");

	if (alpha >= 1.0f)
	{
		alpha = 1.0f;
		draw = &Select::NormalDraw;
	}
	else
	{
		SetAlpha(1.0f);
	}
}

// �t�F�[�h�A�E�g
void Select::FadeOut(void)
{
}

// �ʏ�`��
void Select::NormalDraw(void)
{
	Scene::Draw("QuarterNote");
	Scene::Draw("QuarterNote1");
}

// �`��
void Select::Draw(void)
{
	(this->*draw)();
}

// �L�[����
void Select::Key(void)
{
}

// MIDI����
void Select::Midi(void)
{
}

// ����
void Select::UpData(void)
{
	(this->*updata)();
}

