#pragma once
#include <Windows.h>
#include <vector>
#include <string>

class MIDI_IN
{
public:
	// �R���X�g���N�^
	MIDI_IN();
	// �f�X�g���N�^
	~MIDI_IN();

	// �ڑ�MIDI�f�o�C�X�̐����擾
	UINT GetDevNum(void) const {
		return devNum;
	}
	// �X�e�[�^�X�o�C�g�̎擾
	static UCHAR GetState(void) {
		return state;
	}
	// �f�[�^�o�C�g1�E�m�[�g�i���o�[
	static UCHAR GetData1(void) {
		return data1;
	}
	// �f�[�^�o�C�g2�E�x���V�e�B�[
	static UCHAR GetData2(void) {
		return data2;
	}

private:
	// MIDI���b�Z�[�W�̊m�F
	static void MimData(DWORD param1, DWORD param2);

	// �R�[���o�b�N�֐�
	static void CALLBACK MidiInProc(HMIDIIN handle, UINT msg,
		DWORD instance, DWORD param1, DWORD param2);

	// �G���[���b�Z�[�W
	void Error(const std::string& m);

	// �ڑ�MIDI�f�o�C�X�̐��\���i�[
	void SetMidiCaps(void);

	// MIDI���̓f�o�C�X�̃I�[�v��
	HRESULT Open(UINT index = 0);

	// �V�X�e���G�N�X�N���[�V�u�̒ǉ�
	HRESULT Prepare(void);

	// MIDI�f�o�C�X�̓��͊J�n
	HRESULT Start(void);

	// MIDI�f�o�C�X�̓��͒�~
	HRESULT Stop(void);

	// MIDI�f�o�C�X�̃��Z�b�g
	HRESULT Reset(void);

	// �V�X�e���G�N�X�N���[�V�u�̃N���[���A�b�v
	HRESULT UnPrepare(void);

	// MIDI�f�o�C�X�̓��͏I��
	HRESULT Close(void);


	// �Q�ƌ���
	HRESULT result;

	// MIDI�f�o�C�X�̃n���h��
	HMIDIIN handle;

	// MIDI���̓f�o�C�X�̐�
	UINT devNum;

	// �V�X�e���G�N�X�N���[�V�u�i�[�\����
	MIDIHDR header;

	//MIDI���̓f�o�C�X�̐��\�i�[�\����
	std::vector<MIDIINCAPS>caps;

	// �X�e�[�^�X�o�C�g
	static UCHAR state;

	// �f�[�^�o�C�g1
	static UCHAR data1;

	// �f�[�^�o�C�g2
	static UCHAR data2;
};
