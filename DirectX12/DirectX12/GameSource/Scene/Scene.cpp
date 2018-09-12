#include "Scene.h"
#include "../../Source/Func/Func.h"
#include <sstream>
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
void Scene::AddImg(const std::string & fileName, const Vec2f& size, const Vec2f& pos, float large)
{
	auto start = fileName.find_last_of('/') + 1;
	auto end  = fileName.find_last_of('.');
	std::string name = fileName.substr(start, end - start);

	UINT num = 0;
	std::ostringstream st;
	while (data.find(name) != data.end())
	{
		++num;
		st << num << std::flush;
		name += st.str();
		if (data.find(name) != data.end())
		{
			name.pop_back();
		}
		st.str("");
	}

	LoadImg(data[name].id, fileName);
	data[name].pos   = pos;
	data[name].size  = size;
	data[name].large = large;
}

// �`��
void Scene::Draw(const std::string& name, bool turnX, bool turnY)
{
	auto size = data[name].size * data[name].large;
	func::Draw(data[name].id, data[name].pos.x - (size.x - data[name].size.x) / 2, data[name].pos.y - (size.y - data[name].size.y) / 2, size.x, size.y, turnX, turnY);
}

// �摜����
void Scene::Delete(const std::string & name)
{
	DeleteImg(data[name].id);
}
