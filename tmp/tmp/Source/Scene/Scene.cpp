#include "Scene.h"
#include "../Game/Game.h"
#include "../ImageMane/ImageMane.h"
#include "DxLib.h"

// コンストラクタ
Scene::Scene() : 
	game(Game::Get()), mane(ImageMane::Get()), alpha(255), fadeSpeed(5)
{
	image.clear();
}

// デストラクタ
Scene::~Scene()
{
}

// 画像の読み込み
void Scene::Load(const std::string & fileName, const std::string & name, const Vec2 & size, const Vec2 & pos)
{
	image[name].image = mane.LoadImg(fileName);
	image[name].size  = size;
	image[name].pos   = pos;
}

// 描画
int Scene::DrawGraph(const std::string & name)
{
	return DxLib::DrawGraph(image[name].pos.x, image[name].pos.y, image[name].image, true);
}

// 描画・自由変形
int Scene::DrawModiGraph(const std::string & name)
{
	return DxLib::DrawModiGraph(image[name].pos.x, image[name].pos.y, image[name].pos.x + image[name].size.x, image[name].pos.y,
		image[name].pos.x + image[name].size.x, image[name].pos.y + image[name].size.y, image[name].pos.x, image[name].pos.y + image[name].size.y,
		image[name].image, true);
}
