#pragma once
#include "../Scene.h"
#include <vector>
#include <memory>

class GameMane;
class Mouse;
class BackGround;

class Play :
	public Scene
{
	struct Command {
		//���O
		std::string name;
		//���W
		Vec2 pos;
		//�T�C�Y
		Vec2 size;
		//�F
		unsigned int color;
		//�I�t�Z�b�g
		Vec2 offset;
	};
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
	// �R�}���h�̃Z�b�g
	void SetCom(int index, const std::string name, const Vec2& pos = 0, const Vec2& size = 0);

	// �R�}���h�̏�����
	void ComInit(void);

	// �퓬�`��
	void BattleDraw(void);

	// �I���`��
	void EndDraw(void);

	// �퓬����
	void BattleUpData(void);

	// �I������
	void EndUpData(void);
	

	// �Q�[���}�l
	GameMane& mane;

	// �}�E�X
	Mouse& mouse;

	// �w�i
	std::shared_ptr<BackGround>back;

	// �I�𒆂̃L����
	int select;

	// �^�[�Q�b�g
	int target;

	// �퓬�R�}���h
	std::vector<Command>com;

	// �֐��|�C���^
	void (Play::*draw)(void);
	void (Play::*updata)(void);
};

