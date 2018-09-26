#pragma once
#include "../etc/Vector2.h"

class Game;

class Mouse
{
public:
	// �f�X�g���N�^
	~Mouse();

	// �C���X�^���X�ϐ��̎擾

	static Mouse& Get(void) {
		static Mouse instance;
		return instance;
	}

	// ����
	void UpData(void);

	// ���N���b�N
	bool Click(void) {
		return (state != 0);
	}

	// ���g���K�[�N���b�N
	bool TrigerClick(void) {
		return (state != 0 && old_state == 0);
	}

	// ���W�̎擾
	Vec2 GetPos(void) const {
		return pos;
	}

private:
	// �R���X�g���N�^
	Mouse();
	Mouse(const Mouse&) {
	}
	void operator=(const Mouse&) {
	}


	// ���W
	Vec2 pos;

	// ���݂̏��
	int state;

	// �ߋ��̏��
	int old_state;
};
