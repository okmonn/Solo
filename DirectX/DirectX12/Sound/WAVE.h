#pragma once
#include "VoiceCallback.h"
#include <iostream>
#include <vector>
#include <string>

class WAVE
{
public:
	// �R���X�g���N�^
	WAVE();
	// �f�X�g���N�^
	~WAVE();

	// �ǂݍ���
	int Load(const std::string& fileName);

	// �����f�[�^�̓ǂݍ���
	int Load(void);

	// �C���f�b�N�X�̎擾
	int GetIndex(void) const {
		return index == 0 ? 1 : 0;
	}
	// �Đ����t���O�̎擾
	bool GetStart(void) const {
		return start;
	}
	// �Đ����̃t���O�X�V
	void SetStart(const bool& flag) {
		start = flag;
	}
	// �ǂݍ��ݏI���t���O�̎擾
	bool GetEnd(void) const {
		return end;
	}
	// �ǂݍ��ݏI���t���O�̍X�V
	void SetEnd(const bool& flag) {
		end = flag;
	}


	// �t�H�[�}�b�g
	WAVEFORMATEX format;

	// �R�[���o�b�N
	VoiceCallback callback;

	// �f�[�^
	std::vector<std::vector<BYTE>>data;

private:
	// �����m�F
	int CheckChar(unsigned char * data, int dataSize, const std::string & find);


	// �t�@�C��
	FILE * file;

	// �C���f�b�N�X
	int index;

	// ���݂̓ǂݍ��݃o�C�g��
	int read;

	// �ő�ǂݍ��݃o�C�g��
	int readMax;

	// �Đ����t���O
	bool start;

	// �ǂݍ��ݏI���t���O
	bool end;
};
