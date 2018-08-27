#pragma once
#include "etc/Vector2.h"
#include "etc/Vector3.h"
#include <dinput.h>
#include <string>

typedef unsigned int UINT;
typedef unsigned char UCHAR;

namespace func {
	// �E�B���h�E�T�C�Y�̃Z�b�g
	void SetWindowSize(unsigned int x, unsigned int y);

	// ������
	void Init(void);

	// ���b�Z�[�W�̊m�F
	bool CheckMsg(void);

	// �`�揀��
	void Set(void);

	// ���s
	void Do(void);

	// �L�[����
	bool CheckKey(unsigned int index);

	// �g���K�[�L�[����
	bool TriggerKey(unsigned int index);

	// �摜�ǂݍ���
	void LoadImg(unsigned int& index, const std::string& fileName);

	// �`��
	void Draw(unsigned int& index, float x, float y, bool turnX = false, bool turnY = false);

	// �`��E�T�C�Y�w��
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY, bool turnX = false, bool turnY = false);

	// �`��E�T�C�Y�w��E����
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY, 
		float rectX, float rectY, float rectSizeX, float rectSizeY, bool turnX = false, bool turnY = false);

	// WAVE�̓ǂݍ���
	void LoadWave(unsigned int& index, const std::string fileName);

	// WAVE�̍Đ�
	void PlayWave(unsigned int& index);

	// WAVE�̒�~
	void StopWave(unsigned int& index);

	// MIDI�f�o�C�X�̐��擾
	unsigned int GetMidiDevNum(void);

	// MIDI�X�e�[�^�X�o�C�g�̎擾
	unsigned char GetMidiState(void);

	// MIDI�f�[�^�o�C�g1�̎擾
	unsigned char GetMidiData1(void);

	// MIDI�f�[�^�o�C�g2�̎擾
	unsigned char GetMidiData2(void);
}
