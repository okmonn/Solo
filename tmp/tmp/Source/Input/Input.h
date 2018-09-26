#pragma once
class Input
{
public:
	// �f�X�g���N�^
	~Input();

	// �C���X�^���X�ϐ��̎擾
	static Input& Get(void) {
		static Input instance;
		return instance;
	}

	// ����
	void UpData(void);

	// �L�[�g���K�[�̃`�F�b�N
	bool CheckTrigger(int key) const {
		return (state & key) && !(old_state & key);
	}
	// ���݂̃L�[������Ԃ̃`�F�b�N
	bool CheckPress(int key) const {
		return (state & key);
	}

private:
	// �R���X�g���N�^
	Input();
	Input(const Input&) {
	}
	void operator=(const Input&) {
	}


	// ���݂̃L�[���
	int state;

	// �O�̃L�[���
	int old_state;
};

