#include "Choose.h"
#include "../Play/Play.h"
#include "../../ImageMane/ImageMane.h"
#include "../../GameMane/GameMane.h"
#include "../../Mouse/Mouse.h"

// アニメーション移行フレーム
#define FLAM_MAX 10

// コンストラクタ
Choose::Choose() : image(ImageMane::Get()), mane(GameMane::Get()), mouse(Mouse::Get()), 
	flam(0), index(0)
{
	handle.clear();

	Load();
}

// デストラクタ
Choose::~Choose()
{
}

// 画像読み込み
void Choose::Load(void)
{
	handle.resize(mane.GetID().size());
	for (unsigned int i = 0; i < handle.size(); ++i)
	{
		handle[i] = image.LoadImg("Material/img" + mane.GetID(i) + ".png");
	}
}

// 描画
void Choose::Draw(void)
{
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
}

