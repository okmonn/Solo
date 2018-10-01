#pragma once
#include "Scene.h"
#include <vector>
#include <memory>

class Game;
class GameMane;
class Mouse;
class Stage;
class BackGround;

class BasePlay :
	public Scene
{
	// �R�}���h
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
	BasePlay();
	// �f�X�g���N�^
	virtual ~BasePlay();

	// �`��
	virtual void Draw(void) = 0;

	// ����
	virtual void UpData(void) = 0;

protected:
	// �R�}���h�̃Z�b�g
	void SetCom(int index, const std::string name, const Vec2& pos = 0, const Vec2& size = 0);

	// �R�}���h�̏�����
	void ComInit(void);

	// �G�̓ǂݍ���
	void LoadEnemy(void);

	// �퓬�O�̕`��
	void SetDraw(void);

	// �퓬���̏���
	void ButtleDraw(void);

	// �퓬�I�����̏���
	void EndDraw(void);

	// �R�}���h�̏���
	void ComUpData(void);

	// �^�[�Q�b�g�̃Z�b�g
	void SetTarget(void);

	// �I���L�����̃Z�b�g
	void SetSelect(void);

	// �v���C���[�L�����̍U��
	void Attack_PL(void);

	// �G�L�����̍U��
	void Attack_EN(void);

	// �퓬���̏���
	void ButtleUpData(void);

	// �퓬�I�����̏���
	void EndUpData(void);


	// �Q�[��
	Game& game;

	// �Q�[���}�l
	GameMane& mane;

	// �}�E�X
	Mouse& mouse;

	// �X�e�[�W
	Stage& stage;

	// �w�i
	std::shared_ptr<BackGround> back;

	// �I�𒆂̃L����
	int select;

	// �^�[�Q�b�g
	int target;

	// �o�ߎ���
	int flam;

	// �R�}���h
	std::vector<Command>com;
};

