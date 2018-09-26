#include "BackGround.h"
#include "../ImageMane/ImageMane.h"
#include "DxLib.h"

// コンストラクタ
BackGround::BackGround() : 
	image(ImageMane::Get().LoadImg("Material/img/BackGround.png")), pos(0), size({ 640, 480 })
{
}

// デストラクタ
BackGround::~BackGround()
{
}

// 描画
void BackGround::Draw(void)
{
	DrawGraph(pos.x, pos.y, image, true);
}
