#include "Select.h"
#include "../Play/Play.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
#include <random>
#include <functional>
#include <sstream>
#include <thread>
using namespace func;

// 音符画像最大数
#define QuarterNote_MAX 5

Vec2f pos = 0.0f;

// コンストラクタ
Select::Select() :
	drawCnt(0), flag(false), index(0)
{
	song.clear();
	song = GetDirFile("Material/wave");
	for (UINT i = 0; i < song.size(); ++i)
	{
		auto tmp = song[i];
		song[i] = tmp.substr(0, tmp.find_last_of('.')) + ".png";
	}

	draw = &Select::FadeIn;
	updata = (GetMidiDevNum() <= 0) ? &Select::Key : &Select::Midi;

	MT(drawCnt, 1, QuarterNote_MAX - 1);
	Load();
}

// デストラクタ
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
	
	for (UINT i = 0; i < song.size(); ++i)
	{
		Delete(song[i]);
	}
}

// 読み込み
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

	for (UINT i = 0; i < song.size(); ++i)
	{
		AddImg("Material/img/" + song[i], { 380.0f, 100.0f });
		song[i] = song[i].substr(0, song[i].find_last_of('.'));
	}
}

// メルセンヌツイスタ
void Select::MT(Vec2f & pos, const Vec2f& offset)
{
	//予測不能な乱数を生成
	std::random_device device;
	//指定された範囲の値が等確率で発生するよう離散分布する
	auto x = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().x - (UINT)offset.x)), std::mt19937_64(device()));
	auto y = std::bind(std::uniform_int_distribution<UINT>(0, (Game::Get().GetWinSize().y - (UINT)offset.y)), std::mt19937_64(device()));
	pos.x = static_cast<float>(x());
	pos.y = static_cast<float>(y());
}

// メルセンヌツイスタ
void Select::MT(unsigned int& i, unsigned int min, unsigned int max)
{
	std::random_device device;
	auto tmp = std::bind(std::uniform_int_distribution<UINT>(min, max), std::mt19937_64(device()));
	i = tmp();
}

// フェードイン
void Select::FadeIn(void)
{
	alpha += FADE_SPEED;

	SetAlpha(alpha);

	Scene::Draw(song[index]);
	
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

// フェードアウト
void Select::FadeOut(void)
{
	alpha -= FADE_SPEED;

	SetAlpha(alpha);

	Scene::Draw(song[index]);

	if (alpha <= 0.0f)
	{
		Game::Get().ChangeScene(new Play());
	}
	else
	{
		SetAlpha(1.0f);
	}
}

// 通常描画
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

	Scene::Draw(song[index]);
}

// 描画
void Select::Draw(void)
{
	(this->*draw)();
}

// キー入力
void Select::Key(void)
{
	if (TriggerKey(INPUT_A))
	{
		index = (index + 1 > (int)(song.size()) - 1) ? 0 : ++index;
	}
	else if (TriggerKey(INPUT_RBRACKET))
	{
		index = (index - 1 < 0) ? song.size() - 1 : --index;
	}
	else if (TriggerKey(INPUT_RETURN))
	{
		alpha = 1.0f;
		draw = &Select::FadeOut;
	}
}

// MIDI入力
void Select::Midi(void)
{
}

// 処理
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

				//座標を比較する
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

						//座標の再セット
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

