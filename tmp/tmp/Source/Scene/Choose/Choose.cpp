#include "Choose.h"
#include "../Play/Play.h"
#include "../../Game/Game.h"
#include "../../ImageMane/ImageMane.h"
#include "../../GameMane/GameMane.h"
#include "../../Mouse/Mouse.h"
#include "DxLib.h"

// アニメーション移行フレーム
#define FLAM_MAX 10

// クリック範囲のオフセット
#define BOX_OFFSET 15

// 矢印オフセット
#define ALLREY_OFFSET 15

// 配置座標
const std::vector<Vec2>pos = {
	{50,  200}, 
	{250, 200}, 
	{450, 200},
};

// コンストラクタ
Choose::Choose() : image(ImageMane::Get()), mane(GameMane::Get()), mouse(Mouse::Get()),
	flam(0), index(0), size(64), large(2), target(0), playPos({ 500, 380 }), playSize({ 90, 60 }), color(GetColor(255,255,255))
{
	select.resize(pos.size());
	handle.clear();

	Load();
	InitSelect();
}

// デストラクタ
Choose::~Choose()
{
}

// 選択インデックスの初期化
void Choose::InitSelect(void)
{
	for (unsigned int i = 0; i < select.size(); ++i)
	{
		select[i] = i;
	}
}

// 画像読み込み
void Choose::Load(void)
{
	handle.resize(mane.GetID().size());
	for (unsigned int i = 0; i < handle.size(); ++i)
	{
		handle[i] = image.LoadImg("Material/img/" + mane.GetID(i) + ".png");
	}
}

// 描画
void Choose::Draw(void)
{
	//矢印
	for (int i = 0; i < 2; ++i)
	{
		DrawTriangle(pos[target].x + (size.x * large * i) + ALLREY_OFFSET * (2 - (1 + i) - i), pos[target].y + (size.y * large) / 2 - ALLREY_OFFSET * 2,
			pos[target].x + (size.x * large * i) - ALLREY_OFFSET * (2 - (1 + i) - i), pos[target].y + (size.y * large) / 2,
			pos[target].x + (size.x * large * i) + ALLREY_OFFSET * (2 - (1 + i) - i), pos[target].y + (size.y * large) / 2 + ALLREY_OFFSET * 2,
			GetColor(255, 255, 255), true);
	}

	for (unsigned int i = 0; i < select.size(); ++i)
	{
		DrawRectModiGraph(pos[i].x, pos[i].y,
			pos[i].x + size.x * large, pos[i].y,
			pos[i].x + size.x * large, pos[i].y + size.y * large,
			pos[i].x, pos[i].y + size.y * large,
			size.x * index, size.y * index, size.x, size.y, handle[select[i]], true);
	}

	DrawBox(pos[target].x - BOX_OFFSET, pos[target].y - BOX_OFFSET, 
		pos[target].x + size.x * large + BOX_OFFSET, pos[target].y + size.y * large + BOX_OFFSET, GetColor(255, 0, 0), false);

	DrawBox(500 - 10, 380 - 10, 580, 430, GetColor(0, 255, 0), true);
	DrawString(playPos.x, playPos.y, "バトル", color, false);
}

// 処理
void Choose::UpData(void)
{
	++flam;
	if (flam >= FLAM_MAX)
	{
		index = (index + 1 >= 3) ? 0 : ++index;
		flam = 0;
	}

	for (unsigned int i = 0; i < select.size(); ++i)
	{
		if ((pos[i].x - BOX_OFFSET < mouse.GetPos().x && mouse.GetPos().x < pos[i].x + size.x * large + BOX_OFFSET)
			&& (pos[i].y - BOX_OFFSET < mouse.GetPos().y && mouse.GetPos().y < pos[i].y + size.y * large + BOX_OFFSET))
		{
			if (mouse.TrigerClick() == true)
			{
				target = i;
				break;
			}
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		if (((pos[target].x + (size.x * large * i) + ALLREY_OFFSET * (2 - (1 + i) - i) < mouse.GetPos().x && mouse.GetPos().x < pos[target].x + (size.x * large * i) - ALLREY_OFFSET * (2 - (1 + i) - i)
			|| pos[target].x + (size.x * large * i) - ALLREY_OFFSET * (2 - (1 + i) - i) < mouse.GetPos().x && mouse.GetPos().x < pos[target].x + (size.x * large * i) + ALLREY_OFFSET * (2 - (1 + i) - i)))
			&& (pos[target].y + (size.y * large) / 2 - ALLREY_OFFSET * 2 < mouse.GetPos().y && mouse.GetPos().y < pos[target].y + (size.y * large) / 2 + ALLREY_OFFSET * 2))
		{
			if (mouse.TrigerClick() == true)
			{
				unsigned int num = select[target];
				bool flag = true;
				while (flag)
				{
					if (i % 2 == 0)
					{
						num = ((int)num - 1 < 0) ? handle.size() - 1 : --num;
					}
					else
					{
						num = (num + 1 >= handle.size()) ? 0 : ++num;
					}

					for (unsigned int n = 0; n < select.size(); ++n)
					{
						if (target == n)
						{
							continue;
						}

						flag = true;

						if (num == select[n])
						{
							break;
						}
						else
						{
							flag = false;
						}
					}
				}

				select[target] = num;
			}
			break;
		}
	}

	if ((playPos.x - 10 < mouse.GetPos().x && mouse.GetPos().x < playPos.x - 10 + playSize.x)
		&& (playPos.y - 10 < mouse.GetPos().y && mouse.GetPos().y < playPos.y - 10 + playSize.y))
	{
		color = GetColor(255, 0, 0);

		if (mouse.TrigerClick() == true)
		{
			for (unsigned int i = 0; i < select.size(); ++i)
			{
				mane.SetID_PL(i, mane.GetID(select[i]));
			}

			game.ChangeScene(new Play());
		}
	}
	else
	{
		color = GetColor(255, 255, 255);
	}
}
