#pragma once
#include <string>
#include <vector>

class Stage
{
public:
	// �f�X�g���N�^
	~Stage();

	// �C���X�^���X�ϐ��̎擾
	static Stage& Get(void) {
		static Stage instance;
		return instance;
	}

	// �ǂݍ���
	void LoadStage(void);

	// ID�̃N���A
	void Clear(void);

	// �X�e�[�W�C���f�b�N�X�̎擾
	int GetIndex(void) const {
		return index;
	}
	// �X�e�[�W�C���f�b�N�X�̃Z�b�g
	void SetIndex(const int& index) {
		this->index = index;
	}

	// �G��ID�擾
	std::vector<std::string> GetID(void) const {
		return id;
	}
	std::string GetID(const unsigned int& i) const {
		return id[i];
	}

private:
	// �R���X�g���N�^
	Stage();
	Stage(const Stage&) {
	}
	void operator=(const Stage&) {
	}


	// �X�e�[�W�C���f�b�N�X
	int index;

	// �X�e�[�W�̓GID
	std::vector<std::string>id;
};

