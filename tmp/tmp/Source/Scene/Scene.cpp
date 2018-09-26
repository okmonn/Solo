#include "Scene.h"
#include "../Game/Game.h"
#include "../ImageMane/ImageMane.h"
#include "DxLib.h"

// �R���X�g���N�^
Scene::Scene() : 
	game(Game::Get()), mane(ImageMane::Get())
{
	image.clear();
}

// �f�X�g���N�^
Scene::~Scene()
{
}

// �摜�̓ǂݍ���
void Scene::Load(const std::string & fileName, const std::string & name, const Vec2 & size, const Vec2 & pos)
{
	image[name].image = mane.LoadImg(fileName);
	image[name].size  = size;
	image[name].pos   = pos;
}

// �`��
int Scene::DrawGraph(const std::string & name)
{
	return DxLib::DrawGraph(image[name].pos.x, image[name].pos.y, image[name].image, true);
}

// �`��E���R�ό`
int Scene::DrawModiGraph(const std::string & name)
{
	return DxLib::DrawModiGraph(image[name].pos.x, image[name].pos.y, image[name].pos.x + image[name].size.x, image[name].pos.y,
		image[name].pos.x + image[name].size.x, image[name].pos.y + image[name].size.y, image[name].pos.x, image[name].pos.y + image[name].size.y,
		image[name].image, true);
}
