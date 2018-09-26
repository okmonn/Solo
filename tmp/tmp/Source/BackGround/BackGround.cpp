#include "BackGround.h"
#include "../ImageMane/ImageMane.h"
#include "DxLib.h"

// �R���X�g���N�^
BackGround::BackGround() : 
	image(ImageMane::Get().LoadImg("Material/img/BackGround.png")), pos(0), size({ 640, 480 })
{
}

// �f�X�g���N�^
BackGround::~BackGround()
{
}

// �`��
void BackGround::Draw(void)
{
	DrawGraph(pos.x, pos.y, image, true);
}
