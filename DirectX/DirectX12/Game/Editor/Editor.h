#pragma once
#include "../etc/Share.h"
#include <vector>
#include <string>
#include <string>

class Editor
{
public:
	// �R���X�g���N�^
	Editor();
	// �f�X�g���N�^
	~Editor();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

	// �Z�[�u
	bool Save(void);

	// �ǂݍ���
	bool Load(void);

private:
	// �m�[�c�̃Z�b�g
	void SetNote(LaneType type, unsigned int key1, unsigned int key2, unsigned int key3);

	// ��������
	void Scan(std::string m);

	// �o�߃t���[��
	int flam;

	// ��������
	Notes note[LaneType::TYPE_MAX];

	// ���ʃf�[�^
	std::vector<Notes>data;
};

