#pragma once
#include "NoteNomber.h"
#include <Windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>

class MIDI_IN
{
public:
	// �R���X�g���N�^
	MIDI_IN();
	MIDI_IN(UINT index);
	// �f�X�g���N�^
	~MIDI_IN();

	// MIDI���̓f�o�C�X�̃I�[�v��
	bool Open(UINT index = 0);

	// �ڑ��f�o�C�X���̎擾
	UINT GetDevNum(void) const {
		return devNum;
	}

private:
	// �G���[���b�Z�[�W
	void Error(std::string m);

	// �ڑ�MIDI�f�o�C�X�̐����擾
	void SearchDevNum(void);

	// �ڑ��ς݂�MIDI�f�o�C�X�̐��\���i�[
	void SetMidiCaps(void);

	// �R�[���o�b�N�֐�
	static void CALLBACK MidiInProc(HMIDIIN handle, UINT msg,
		DWORD instance, DWORD param1, DWORD param2);

	// SysEx�̃o�b�t�@�o�^
	bool SetSysExBuffer(void);

	// �w�肵��MIDI�f�o�C�X�ł̓��͂̊J�n
	bool Start(void);

	// �w�肵��MIDI�f�o�C�X�ł̓��͂̏I��
	bool Stop(void);

	// �w�肵��MIDI�f�o�C�X�ł̓��͂̒�~
	bool MidiReset(void);

	// SysEx�o�b�t�@�̃N���[���A�b�v
	bool ClearHdr(void);

	// MIDI���̓f�o�C�X�̃N���[�Y
	bool Close(void);

	// ���Z�b�g
	void Reset(void);


	// �Q�ƌ���
	MMRESULT result;

	// MIDI�f�o�C�X�̃n���h��
	HMIDIIN handle;

	// MIDI���̓f�o�C�X�̐�
	UINT devNum;

	// �V�X�e���G�N�X�N���[�V�u�i�[�\����
	MIDIHDR header;

	//MIDI���̓f�o�C�X�̐��\�i�[�\����
	std::vector<MIDIINCAPS>caps;

	// �V�X�e���G�N�X�N���[�V�u�i�[�\���̂̃A�h���X
	static MIDIHDR* hdr;

	// �X�e�[�^�X�o�C�g
	static UCHAR state;

	// �m�[�g�ԍ�
	static UCHAR note;

	// �x���V�e�B�[
	static UCHAR vel;
};

class MIDI_OUT
{
public:
	// �R���X�g���N�^
	MIDI_OUT();
	MIDI_OUT(UINT index);
	// �f�X�g���N�^
	~MIDI_OUT();

	// MIDI���̓f�o�C�X�̃I�[�v��
	bool Open(UINT index = 0);

	// ���F�̃m�[�g�I��
	bool TimbreOn(DWORD no, DWORD vel = 0x007f0000);

	// �m�[�g�I��
	bool On(DWORD no, DWORD vel = 0x007f0000, DWORD change = AcousticGrandPiano, DWORD channel = Channel1);

	// �m�[�g�I�t
	bool Off(DWORD no);

	// �ڑ��f�o�C�X���̎擾
	UINT GetDevNum(void) const {
		return devNum;
	}

private:
	// �G���[���b�Z�[�W
	void Error(std::string m);

	// �ڑ��o�̓f�o�C�X�̐����擾
	void SearchDevNum(void);

	// �ڑ��ς݂̏o�̓f�o�C�X�̐��\���i�[
	void SetMidiCaps(void);

	// SysEx���b�Z�[�W�̑��M
	bool SendSysEx(void);

	// �v���O�����`�F���W
	bool ProgramChange(DWORD no, DWORD channel = Channel1);

	// �w�肵��MIDI�f�o�C�X�ł̏o�͂̒�~
	bool MidiReset(void);

	// SysEx�o�b�t�@�̃N���[���A�b�v
	bool ClearHdr(void);

	// MIDI�o�̓f�o�C�X�̃N���[�Y
	bool Close(void);


	// �Q�ƌ���
	MMRESULT result;

	// �n���h��
	HMIDIOUT handle;

	// MIDI�o�̓f�o�C�X�̐�
	UINT devNum;

	// �V�X�e���G�N�X�N���[�V�u�i�[�\����
	MIDIHDR header;

	//MIDI�o�̓f�o�C�X�̐��\�i�[�\����
	std::vector<MIDIOUTCAPS>caps;
};
