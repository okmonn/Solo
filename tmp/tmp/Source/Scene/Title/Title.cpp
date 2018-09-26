#include "Title.h"
#include "../../Game/Game.h"
#include "../../Mouse/Mouse.h"
#include "../Select/Select.h"
#include "DxLib.h"
#include <functional>
#include <random>

// 円の最大数
#define CIRCLE_MAX 30

// 円の最大半径
#define RADIUS_MAX 255

// コンストラクタ
Title::Title() : 
	mouse(Mouse::Get())
{
	circle.resize(CIRCLE_MAX);

	CircleInit();
}

// デストラクタ
Title::~Title()
{
}

// 円の初期化
void Title::CircleInit(void)
{
	//予測不能な乱数を生成
	std::random_device device;

	for (unsigned int i = 0; i < circle.size(); ++i)
	{
		circle[i].radius = 0;

		auto flag = std::bind(std::uniform_int_distribution<int>(0, 100), std::mt19937_64(device()));
		circle[i].flag = (flag() % 3 == 0) ? true : false;

		auto color = std::bind(std::uniform_int_distribution<unsigned int>(1, GetColor(255, 255, 255)), std::mt19937_64(device()));
		circle[i].color = color();

		auto x = std::bind(std::uniform_int_distribution<int>(0, (game.GetWinSize().x)), std::mt19937_64(device()));
		auto y = std::bind(std::uniform_int_distribution<int>(0, (game.GetWinSize().y)), std::mt19937_64(device()));
		circle[i].pos = { x(), y() };
	}
}

// 描画
void Title::Draw(void)
{
	for (unsigned int i = 0; i < circle.size(); ++i)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - circle[i].radius);
		DrawCircle(circle[i].pos.x, circle[i].pos.y, circle[i].radius, circle[i].color, false);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(250, 250, "タイトル", GetColor(255, 0, 0), false);
}

// 処理
void Title::UpData(void)
{
	if (mouse.TrigerClick())
	{
		game.ChangeScene(new Select());
	}

	for (unsigned int i = 0; i < circle.size(); ++i)
	{
		if (circle[i].flag == true)
		{
			++circle[i].radius;
			if (circle[i].radius > RADIUS_MAX)
			{
				circle[i].flag = false;
			}
		}
		else
		{
			//予測不能な乱数を生成
			std::random_device device;

			circle[i].radius = 0;

			auto flag = std::bind(std::uniform_int_distribution<int>(0, 100), std::mt19937_64(device()));
			circle[i].flag = (flag() % 3 == 0) ? true : false;

			auto color = std::bind(std::uniform_int_distribution<unsigned int>(1, GetColor(255, 255, 255)), std::mt19937_64(device()));
			circle[i].color = color();

			auto x = std::bind(std::uniform_int_distribution<int>(0, (game.GetWinSize().x)), std::mt19937_64(device()));
			auto y = std::bind(std::uniform_int_distribution<int>(0, (game.GetWinSize().y)), std::mt19937_64(device()));
			circle[i].pos = { x(), y() };
		}
	}
}
