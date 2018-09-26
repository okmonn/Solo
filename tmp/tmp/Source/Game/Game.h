#pragma once
#include "../etc/Vector2.h"
#include <memory>

class Scene;

class Game
{
public:
	// �f�X�g���N�^
	~Game();

	// �C���X�^���X�ϐ��̎擾
	static Game& Get(void) {
		static Game instance;
		return instance;
	}

	// ����
	void Run(void);

	// �V�[���ڍs
	void ChangeScene(Scene* scene);

	// �E�B���h�E�T�C�Y�̎擾
	Vec2 GetWinSize(void) const {
		return size;
	}

	// �t�H���g�T�C�Y�̎擾
	int GetFontSize(void) const {
		return fontSize;
	}

private:
	// �R���X�g���N�^
	Game();
	Game(const Game&) {
	}
	void operator=(const Game&) {
	}

	// ������
	void Init(void);

	// �`��
	void Draw(void); 

	// ����
	void UpData(void);

	// �I������
	void End(void);


	// �V�[��
	std::shared_ptr<Scene>scene;

	// �E�B���h�E�T�C�Y
	Vec2 size;

	// �t�H���g�T�C�Y
	int fontSize;
};

