#include "Choose.h"
#include "../Play/Play.h"
#include "../../ImageMane/ImageMane.h"
#include "../../GameMane/GameMane.h"
#include "../../Mouse/Mouse.h"

// �A�j���[�V�����ڍs�t���[��
#define FLAM_MAX 10

// �R���X�g���N�^
Choose::Choose() : image(ImageMane::Get()), mane(GameMane::Get()), mouse(Mouse::Get()), 
	flam(0), index(0)
{
	handle.clear();

	Load();
}

// �f�X�g���N�^
Choose::~Choose()
{
}

// �摜�ǂݍ���
void Choose::Load(void)
{
	handle.resize(mane.GetID().size());
	for (unsigned int i = 0; i < handle.size(); ++i)
	{
		handle[i] = image.LoadImg("Material/img" + mane.GetID(i) + ".png");
	}
}

// �`��
void Choose::Draw(void)
{
}

// ����
void Choose::UpData(void)
{
	++flam;
	if (flam >= FLAM_MAX)
	{
		index = (index + 1 >= 3) ? 0 : ++index;
		flam = 0;
	}
}

