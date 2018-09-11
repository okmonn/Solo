#pragma once
#include "../../Source/etc/Vector2.h"
#include <map>
#include <string>

class Scene
{
	// �f�[�^
	struct Data {
		//�摜�f�[�^
		unsigned int id;
		//���W
		Vec2f pos;
		//�T�C�Y
		Vec2f size;
	};

public:
	// �R���X�g���N�^
	Scene();
	// �f�X�g���N�^
	virtual ~Scene();

	// �`��
	virtual void Draw(void) = 0;
	// ����
	virtual void UpData(void) = 0;

protected:
	// �摜�f�[�^�̒ǉ�
	void AddImg(const std::string& fileName, const Vec2f& size, const Vec2f& pos = 0.0f);

	// �`��
	void Draw(const std::string& name, float large = 1.0f, bool turnX = false, bool turnY = false);

	// �摜�f�[�^
	std::map<std::string, Data>data;

	// �A���t�@�l
	float alpha;
};
