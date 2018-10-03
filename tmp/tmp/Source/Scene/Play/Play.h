#pragma once
#include "../BasePlay.h"
#include <vector>
#include <memory>

class GameMane;
class Mouse;
class Stage;
class BackGround;

class Play :
	public BasePlay
{
public:
	// �R���X�g���N�^
	Play();
	// �f�X�g���N�^
	~Play();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �t�F�[�h�C��
	void FadeIn(void);

	// �퓬�O����
	void SetUpData(void);

	// �F
	unsigned int color;

	// �֐��|�C���^
	void (Play::*draw)(void);
	void (Play::*updata)(void);
};

