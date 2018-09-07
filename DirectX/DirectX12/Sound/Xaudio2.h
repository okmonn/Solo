#pragma once
#include <xaudio2.h>
#include <map>
#include <thread>

class WAVE;

class Xaudio2
{
public:
	// �R���X�g���N�^
	Xaudio2();
	// �f�X�g���N�^
	~Xaudio2();

	// �ǂݍ���
	HRESULT LoadWAVE(UINT& index, const std::string& fileName);

	// �Đ��J�n
	HRESULT Play(UINT& index, bool loop);

	// �Đ���~
	HRESULT Stop(UINT& index);

	// �\�[�X�{�C�X�̏���
	void Delete(UINT& index);

private:
	// ������
	HRESULT Init(void);

	// XAudio2�̐���
	HRESULT CreateAudio(void);

	// �f�o�b�O�̃Z�b�g
	void SetDebug(void);

	// �}�X�^�[�{�C�X�̐���
	HRESULT CreateMaster(void);

	// �Đ��J�n
	void Start(UINT& index);


	// �Q�ƌ���
	HRESULT result;

	// XAudio2
	IXAudio2 * audio;

	// �}�X�^�[�{�C�X
	IXAudio2MasteringVoice* master;

	// WAVE�f�[�^
	std::map<UINT*, WAVE>wave;

	// �\�[�X�{�C�X
	std::map<WAVE*, IXAudio2SourceVoice*>voice;

	// �X���b�h
	std::map<WAVE*, std::thread>th;
};

