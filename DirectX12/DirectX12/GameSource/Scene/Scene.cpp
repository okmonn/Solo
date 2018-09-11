#include "Scene.h"
#include "../../Source/Func/Func.h"
using namespace func;

// �R���X�g���N�^
Scene::Scene()
{
	data.clear();
}

// �f�X�g���N�^
Scene::~Scene()
{
}

// �摜�f�[�^�̒ǉ�
void Scene::AddImg(const std::string & fileName)
{
	auto start = fileName.find_last_of('/') + 1;
	auto end = fileName.find_last_of('.');
	std::string name = fileName.substr(start, end - start);

	LoadImg(data[name], fileName);
}

// �`��
void Scene::Draw(const std::string& name, const Vec2f& pos, bool turnX, bool turnY)
{
	func::Draw(data[name], pos.x, pos.y, turnX, turnY);
}

// �`��E�T�C�Y�w��
void Scene::Draw(const std::string & name, const Vec2f & pos, const Vec2f & size, bool turnX, bool turnY)
{
	func::Draw(data[name], pos.x, pos.y, size.x, size.y, turnX, turnY);
}
