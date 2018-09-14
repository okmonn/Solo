#include "Select.h"
#include "../Play/Play.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
#include <random>
#include <functional>
#include <sstream>
#include <thread>
using namespace func;

// �����摜�ő吔
#define QuarterNote_MAX 5

Vec2f pos = 0.0f;

// �R���X�g���N�^
Select::Select() :
	drawCnt(0), flag(false), index(0)
{
	song.clear();
	song = GetDirFile("Material/wave");

	draw = &Select::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Select::Key : &Select::Midi;

	MT(drawCnt, 1, QuarterNote_MAX - 1);
	Load();
}

// �f�X�g���N�^
Select::~Select()
{
	for (UINT i = 0; i < QuarterNote_MAX; ++i)
	{
		std::ostringstream st;
		if (i != 0)
		{
			st << i << std::flush;
		}
		Delete("QuarterNote" + st.str());
		st.str("");
	}
	
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

// �����Z���k�c�C�X�^
void Select::MT(Vec2f & pos, const Vec2f& offset)
{
	//�\���s�\�ȗ����𐶐�
	std::random_device device;
	//�w�肳�ꂽ�͈͂̒l�����m���Ŕ�������悤���U���z����
	auto x = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().x - (UINT)offset.x)), std::mt19937_64(device()));
	auto y = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().y - (UINT)offset.y)), std::mt19937_64(device()));
	pos.x = static_cast<float>(x());
	pos.y = static_cast<float>(y());
}

// �����Z���k�c�C�X�^
void Select::MT(unsigned int& i, unsigned int min, unsigned int max)
{
	std::random_device device;
	auto tmp = std::bind(std::uniform_int_distribution<UINT>(min, max), std::mt19937_64(device()));
	i = tmp();
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
	alpha -= FADE_SPEED;

	SetAlpha(alpha);

	Scene::Draw("GameStart");

	if (alpha <= 0.0f)
	{
		Game::Get().ChangeScene(new Play());
	}
	else
	{
		SetAlpha(1.0f);
	}
}

// �ʏ�`��
void Select::NormalDraw(void)
{
	SetAlpha(alpha);
	for (UINT i = 0; i < drawCnt; ++i)
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
	if (TriggerKey(INPUT_A))
	{
		index += (index + 1 >= song.size()) ? 0 : 1;
	}
	else if (TriggerKey(INPUT_RBRACKET))
	{
		index += (index - 1 <= 0) ? song.size() - 1 : -1;
	}
	else if (TriggerKey(INPUT_RETURN))
	{
		alpha = 1.0f;
		draw = &Select::FadeOut;
	}
}

// MIDI����
void Select::Midi(void)
{
}

// ����
void Select::UpData(void)
{
	if (draw != &Select::NormalDraw)
	{
		return;
	}

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
			MT(drawCnt, 1, QuarterNote_MAX - 1);

			for (UINT i = 0; i < drawCnt; ++i)
			{
				std::ostringstream st;
				if (i != 0)
				{
					st << i << std::flush;
				}
				MT(data["QuarterNote" + st.str()].pos, data["QuarterNote" + st.str()].size);

				//���W���r����
				for (UINT n = 0; n < drawCnt; ++n)
				{
					if (i == n)
					{
						continue;
					}
					else
					{
						std::ostringstream tm;
						if (n != 0)
						{
							tm << n << std::flush;
						}

						//���W�̍ăZ�b�g
						std::thread th([&](Vec2f& pos1, Vec2f& size1, Vec2f& pos2, Vec2f& size2) {
							while (true)
							{
								float x = std::abs((pos1.x + size1.x / 2.0f) - (pos2.x + size2.x / 2.0f));
								float y = std::abs((pos1.y + size1.y / 2.0f) - (pos2.y + size2.y / 2.0f));

								if (!(x >= size1.x && y >= size1.y))
								{
									MT(pos1, size1);
								}
								else
								{
									break;
								}
							}
						}, std::ref(data["QuarterNote" + st.str()].pos), std::ref(data["QuarterNote" + st.str()].size), std::ref(data["QuarterNote" + tm.str()].pos), std::ref(data["QuarterNote" + tm.str()].size));

						th.join();
						tm.str("");
					}
				}

				st.str("");
			}
			alpha = 0.0f;
			flag = false;
		}
	}
}

