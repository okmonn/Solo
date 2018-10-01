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
	
	// �퓬�O����
	void SetUpData(void);

	// ���w�ƓG�w�̐���
	void Description1(void);
	

	// �i�s�󋵃J�E���g
	unsigned int cnt;

	// �֐��|�C���^
	void (Tutorial::*draw)(void);
	void (Tutorial::*updata)(void);
};

