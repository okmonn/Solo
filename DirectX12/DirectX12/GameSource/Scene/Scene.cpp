#include "Scene.h"
#include "../../Source/Func/Func.h"
using namespace func;

// �R���X�g���N�^
Scene::Scene() : 
	alpha(0.0f)
{
	data.clear();
}

// �f�X�g���N�^
Scene::~Scene()
{
}

// �摜�f�[�^�̒ǉ�
void Scene::AddImg(const std::string & fileName, const Vec2f& size, const Vec2f& pos)
{
	auto start = fileName.find_last_of('/') + 1;
	auto end  = fileName.find_last_of('.');
	std::string name = fileName.substr(start, end - start);

	LoadImg(data[name].id, fileName);
	data[name].pos  = pos;
	data[name].size = size;
}

// �`��
void Scene::Draw(const std::string& name, float large, bool turnX, bool turnY)
{
	auto size = data[name].size * large;
	func::Draw(data[name].id, data[name].pos.x - (size.x - data[name].size.x) / 2, data[name].pos.y - (size.y - data[name].size.y) / 2, size.x, size.y, turnX, turnY);
}
