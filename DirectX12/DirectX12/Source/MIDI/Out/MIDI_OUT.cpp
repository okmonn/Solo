#include "MIDI_OUT.h"

#pragma comment(lib, "winmm.lib")

BYTE GMSystemOn[] = { 0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7 };

// �R���X�g���N�^
MIDI_OUT::MIDI_OUT() 
	: result(MMSYSERR_NOERROR), handle(nullptr), devNum(0)
{
	header = {};

	SearchDevNum();
	SetMidiCaps();
}

// �R���X�g���N�^
MIDI_OUT::MIDI_OUT(UINT index) 
	: result(MMSYSERR_NOERROR), handle(nullptr), devNum(0)
{
	header = {};

	SearchDevNum();
	SetMidiCaps();
	Open(index);
}

// �f�X�g���N�^
MIDI_OUT::~MIDI_OUT()
{
	MidiReset();
	ClearHdr();
	Close();
}

// �G���[���b�Z�[�W
void MIDI_OUT::Error(const std::string& m)
{
#ifdef UNICODE
	LPWSTR errmsg = 0;
#else
	LPSTR errmsg = 0;
#endif
	midiInGetErrorText(result, errmsg, sizeof(errmsg));
	printf(m.c_str());
	printf("�F%ls\n", errmsg);
}

// �ڑ��o�̓f�o�C�X�̐����擾
void MIDI_OUT::SearchDevNum(void)
{
	devNum = midiOutGetNumDevs();
}

// �ڑ��ς݂̏o�̓f�o�C�X�̐��\���i�[
void MIDI_OUT::SetMidiCaps(void)
{
	caps.resize(devNum);
	for (UINT i = 0; i < devNum; ++i)
	{
		result = midiOutGetDevCaps(i, &caps[i], sizeof(MIDIOUTCAPS));
		if (result != MMSYSERR_NOERROR)
		{
			Error("�L���v�`���[���s");
		}
	}
}

// MIDI���̓f�o�C�X�̃I�[�v��
bool MIDI_OUT::Open(UINT index)
{
	if (devNum <= index)
	{
		return false;
	}

	result = midiOutOpen(&handle, index, 0, 0, 0);
	if (result != MMSYSERR_NOERROR)
	{
		Error("�I�[�v�����s");
		return false;
	}

	if (SendSysEx() == false)
	{
		return false;
	}

	return true;
}

// SysEx���b�Z�[�W�̑��M
bool MIDI_OUT::SendSysEx(void)
{
	header.lpData = (LPSTR)GMSystemOn;
	header.dwBufferLength = sizeof(GMSystemOn);
	header.dwFlags = 0;

	result = midiOutPrepareHeader(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("SysEx�̃Z�b�g���s");
		return false;
	}

	result = midiOutLongMsg(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("SysEx�̑��M���s");
		return false;
	}

	return true;
}

// �v���O�����`�F���W
bool MIDI_OUT::ProgramChange(DWORD no, DWORD channel)
{
	if (channel == 0x000000c9)
	{
		return false;
	}

	DWORD note = channel | no;
	result = midiOutShortMsg(handle, note);
	if (result != MMSYSERR_NOERROR)
	{
		Error("�v���O�����`�F���W���s");
		return false;
	}
	return true;
}

// ���F�̃m�[�g�I��
bool MIDI_OUT::TimbreOn(DWORD no, DWORD vel)
{
	DWORD note = 0x00000099 | no | vel;
	result = midiOutShortMsg(handle, note);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���F�̃m�[�g�I�����s");
		return false;
	}

	return true;
}

// �m�[�g�I��
bool MIDI_OUT::On(DWORD no, DWORD vel, DWORD change, DWORD channel)
{
	if (ProgramChange(change, channel) == false)
	{
		return false;
	}

	DWORD note = 0x00000090 | no | vel;
	result = midiOutShortMsg(handle, note);
	if (result != MMSYSERR_NOERROR)
	{
		Error("�m�[�g�I�����s");
		return false;
	}

	return true;
}

// �m�[�g�I�t
bool MIDI_OUT::Off(DWORD no)
{
	DWORD note = 0x007f0080 | no;
	result = midiOutShortMsg(handle, note);
	if (result != MMSYSERR_NOERROR)
	{
		Error("�m�[�g�I�t���s");
		return false;
	}

	return true;
}

// �w�肵��MIDI�f�o�C�X�ł̏o�͂̒�~
bool MIDI_OUT::MidiReset(void)
{
	result = midiOutReset(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���Z�b�g���s");
		return false;
	}

	return true;
}

// SysEx�o�b�t�@�̃N���[���A�b�v
bool MIDI_OUT::ClearHdr(void)
{
	result = midiOutUnprepareHeader(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("SysEx�̃N���[���A�b�v���s");
		return false;
	}

	return true;
}

// MIDI�o�̓f�o�C�X�̃N���[�Y
bool MIDI_OUT::Close(void)
{
	result = midiOutClose(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("�N���[�Y���s");
		return false;
	}
	return true;
}
