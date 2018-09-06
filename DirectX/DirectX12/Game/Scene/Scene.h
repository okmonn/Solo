#pragma once
#include "../../etc/Vector2.h"
#include <map>
#include <string>

class Scene
{
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
	void AddImg(const std::string& fileName);

	// �`��
	void Draw(const std::string& name, const Vec2f& pos, bool turnX = false, bool turnY = false);

	// �`��E�T�C�Y�w��
	void Draw(const std::string& name, const Vec2f& pos, const Vec2f& size, bool turnX = false, bool turnY = false);

	// �摜�f�[�^
	std::map<std::string, unsigned int>data;
};
