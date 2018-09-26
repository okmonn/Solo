#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <map>

class Game;
class ImageMane;

class Scene
{
	// �摜�f�[�^
	struct Data {
		int image;
		Vec2 size;
		Vec2 pos;
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
	// �摜�̓ǂݍ���
	void Load(const std::string& fileName, const std::string& name, const Vec2& size, const Vec2& pos = 0);

	// �`��
	int DrawGraph(const std::string& name);

	// �`��E���R�ό`
	int DrawModiGraph(const std::string& name);


	// �Q�[��
	Game& game;

	// �C���[�W�}�l�[�W���[
	ImageMane& mane;

	// �摜�f�[�^
	std::map<std::string, Data>image;
};

