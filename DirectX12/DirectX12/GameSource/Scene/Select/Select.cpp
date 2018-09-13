#include "Select.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
#include <random>
#include <functional>
#include <sstream>
using namespace func;

#define QuarterNote_MAX 3

// �R���X�g���N�^
Select::Select() :
	flag(false)
{
	draw = &Select::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Select::Key : &Select::Midi;

	Load();
}

// �f�X�g���N�^
Select::~Select()
{
	Delete("QuarterNote");
	Delete("QuarterNote1");
	Delete("QuarterNote2");
	Delete("GameStart");
}

// �ǂݍ���
void Select::Load(void)
{
	for (UINT i = 0; i < QuarterNote_MAX; ++i)
	{
		std::ostringstream st;
		if (i != 0)
		{
			st << i << std::flush;
		}
		AddImg("Material/img/QuarterNote.png", { 130.0f, 150.0f });
		MT(data["QuarterNote" + st.str()].pos, data["QuarterNote" + st.str()].size);
		st.str("");
	}
	AddImg("Material/img/GameStart.png", { 350.0f, 51.0f }, 
		{ (float)Game::Get().GetWinSize().x / 2.0f - 350.0f / 2.0f, (float)Game::Get().GetWinSize().y / 2.0f - 152.0f / 2.0f });
}

// �t�F�[�h�C��
void Select::FadeIn(void)
{
	alpha += FADE_SPEED;

	SetAlpha(alpha);

	Scene::Draw("GameStart");
	
	if (alpha >= 1.0f)
	{
		alpha = -1.0f;
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
	SetAlpha(alpha);
	for (UINT i = 0; i < QuarterNote_MAX; ++i)
	{
		std::ostringstream st;
		if (i != 0)
		{
			st << i << std::flush;
		}
		Scene::Draw("QuarterNote" + st.str());
		st.str("");
	}
	SetAlpha(1.0f);

	Scene::Draw("GameStart");
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

// �����Z���k�c�C�X�^
void Select::MT(Vec2f & pos, const Vec2f& offset)
{
	std::random_device device;
	auto x = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().x - (UINT)offset.x)), std::mt19937(device()));
	auto y = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().y - (UINT)offset.y)), std::mt19937(device()));
	pos.x = static_cast<float>(x());
	pos.y = static_cast<float>(y());
}

// ����
void Select::UpData(void)
{
	(this->*updata)();

	if (flag == false && alpha < 2.0f)
	{
		alpha += FADE_SPEED;
		if (alpha >= 2.0f)
		{
			alpha = 1.0f;
			flag = true;
		}
	}
	else if (flag == true && alpha > -1.0f)
	{
		alpha -= FADE_SPEED;
		if (alpha <= -1.0f)
		{
			MT(data["QuarterNote"].pos, data["QuarterNote"].size);
			MT(data["QuarterNote1"].pos, data["QuarterNote1"].size);
			MT(data["QuarterNote2"].pos, data["QuarterNote2"].size);
			alpha = 0.0f;
			flag = false;
		}
	}
}

