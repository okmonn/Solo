#pragma once
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

	// �V�[���̈ڍs
	void ChangeScene(Scene* scene);

	// ����
	void Run(void);

private:
	// �R���X�g���N�^
	Game();
	Game(const Game&) {
	}
	void operator=(const Game&) {
	}

	// �N���X�̃C���X�^���X
	void Init(void);

	// �I������
	void End(void);


	// �V�[��
	std::shared_ptr<Scene>scene;
};
