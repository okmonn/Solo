#pragma once
#include "etc/Vector2.h"
#include "etc/Vector3.h"
#include "Input/InputData.h"
#include <Windows.h>
#include <string>
#include <vector>

namespace func {
	// �E�B���h�E�T�C�Y�̃Z�b�g
	void SetWindowSize(unsigned int x, unsigned int y);

	// ������
	void Init(void);

	// ���b�Z�[�W�̊m�F
	bool CheckMsg(void);

	// �r���[�s��̃Z�b�g
	void ChangeView(const Vec3f& pos, const Vec3f& target, const Vec3f& up);

	// �`�揀��
	void Set(void);

	// ���s
	void Do(void);

	// �L�[����
	bool CheckKey(unsigned int index);

	// �g���K�[�L�[����
	bool TriggerKey(unsigned int index);

	// ���l�̐ݒ�
	void SetAlpha(float alpha);

	// �_�̕`��
	void DrawPoint(float x, float y, float r, float g, float b);

	// ���C���̕`��
	void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b);

	// �{�b�N�X�̕`��
	void DrawBox(float x, float y, float sizeX, float sizeY, float r, float g, float b);

	// �摜�ǂݍ���
	void LoadImg(unsigned int& index, const std::string& fileName);

	// �`��
	void Draw(unsigned int& index, float x, float y, bool turnX = false, bool turnY = false);

	// �`��E�T�C�Y�w��
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY, bool turnX = false, bool turnY = false);

	// �`��E�T�C�Y�w��E����
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY,
		float rectX, float rectY, float rectSizeX, float rectSizeY, bool turnX = false, bool turnY = false);

	// �摜�̏���
	void DeleteImg(unsigned int& index);

	// PMD�ǂݍ���
	void LoadPMD(unsigned int& index, const std::string& fileName);

	// PMD�`��
	void DrawPMD(unsigned int& index);

	// PMD�̏���
	void DeletePMD(unsigned int& index);

	// WAVE�̓ǂݍ���
	void LoadWave(unsigned int& index, const std::string fileName);

	// WAVE�̍Đ�
	void PlayWave(unsigned int& index, bool loop = false);

	// WAVE�̒�~
	void StopWave(unsigned int& index);

	// WAVE�̏���
	void DeleteWAVE(unsigned int& index);

	// MIDI�f�o�C�X�̐��擾
	unsigned int GetMidiDevNum(void);

	// MIDI�X�e�[�^�X�o�C�g�̎擾
	unsigned char GetMidiState(void);

	// MIDI�f�[�^�o�C�g1�̎擾
	unsigned char GetMidiData1(void);

	// MIDI�f�[�^�o�C�g2�̎擾
	unsigned char GetMidiData2(void);

	// �w�肵���f�B���N�g���̃t�@�C�����擾
	std::vector<std::string> GetDirFile(const std::string& path);
	std::vector<std::wstring> GetDirFile(const std::wstring& path);

	// ���O�C�����[�U�[�l�[���擾
	std::wstring GetName(void);
}
