#pragma once
#include "../BasePlay.h"

class Tutorial :
	public BasePlay
{
public:
	// �R���X�g���N�^
	Tutorial();
	// �f�X�g���N�^
	~Tutorial();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �v���C���[�̓ǂݍ���
	void LoadPlayer(void);

	// ���������̕\��
	void DrawString(const std::string& mozi);
	
	// �퓬�O����
	void SetUpData(void);

	// ���w�ƓG�w�̐���
	void Description1(void);
	

	// �����o�����W
	Vec2 pos;

	// �����o���T�C�Y
	Vec2 size;

	// �i�s�󋵃J�E���g
	unsigned int cnt;

	// �o�߃t���[��
	unsigned int flam;

	// �C���f�b�N�X
	int index;

	// �����o���C���f�b�N�X
	int num;

	// �\������
	std::vector<std::string> st;

	// �֐��|�C���^
	void (Tutorial::*draw)(void);
	void (Tutorial::*updata)(void);
};

