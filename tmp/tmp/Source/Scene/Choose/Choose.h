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
	// �I���C���f�b�N�X�̏�����
	void InitSelect(void);

	// �摜�ǂݍ���
	void Load(void);

	// �t�F�[�h�C��
	void FadeIn(void);

	// �L�����I��
	void ChooseObj(void);

	// �ʏ폈��
	void Normal(void);

	// �t�F�[�h�A�E�g
	void FadeOut(void);


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

	// �I���C���f�b�N�X
	std::vector<unsigned int>select;

	// �^�[�Q�b�g
	int target;

	// �L�����T�C�Y
	Vec2 size;

	// �g�嗦
	int large;

	// �v���C�ڍs�R�}���h���W
	Vec2 playPos;

	// �v���C�ڍs�R�}���h�T�C�Y
	Vec2 playSize;

	// �F
	unsigned int color;

	// �{�b�N�X�F
	unsigned int b_color;

	// �摜�n���h��
	std::vector<int>handle;

	// �֐��|�C���^
	void (Choose::*func)(void);
};
