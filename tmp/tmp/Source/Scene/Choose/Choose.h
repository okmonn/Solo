#pragma once
#include "../Scene.h"
#include <vector>

class ImageMane;
class GameMane;
class Mouse;

class Choose :
	public Scene
{
public:
	// �R���X�g���N�^
	Choose();
	// �f�X�g���N�^
	~Choose();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �摜�ǂݍ���
	void Load(void);


	// �C���[�W�}�l
	ImageMane& image;

	// �Q�[���}�l
	GameMane& mane;

	// �}�E�X
	Mouse& mouse;

	// �o�߃t���[��
	int flam;

	// �C���f�b�N�X
	unsigned int index;

	// �摜�n���h��
	std::vector<int>handle;
};
