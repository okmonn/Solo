#include "MIDI.h"

#pragma comment(lib, "winmm.lib")

BYTE GMSystemOn[] = { 0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7 };

MIDIHDR* MIDI_IN::hdr = nullptr;
UCHAR MIDI_IN::state = 0;
UCHAR MIDI_IN::note = 0;
UCHAR MIDI_IN::vel = 0;

// �o�b�t�@�T�C�Y
#define BUFFER_SIZE 256

// �R���X�g���N�^
MIDI_IN::MIDI_IN() 
	: result(MMSYSERR_NOERROR), handle(nullptr), devNum(0)
{
	Reset();

	header = {};

	SearchDevNum();
	SetMidiCaps();
}

// �R���X�g���N�^
MIDI_IN::MIDI_IN(UINT index)
	: result(MMSYSERR_NOERROR), handle(nullptr), devNum(0)
{
	Reset();

	header = {};

	SearchDevNum();
	SetMidiCaps();
	Open(index);
}

// �f�X�g���N�^
MIDI_IN::~MIDI_IN()
{
	Stop();
	MidiReset();
	ClearHdr();
	Close();
	Reset();
}

// �G���[���b�Z�[�W
void MIDI_IN::Error(std::string m)
{
	LPWSTR errmsg = 0;
	midiInGetErrorText(result, errmsg, sizeof(errmsg));
	printf(m.c_str());
	printf("�F%ls\n", errmsg);
}

// �ڑ�MIDI�f�o�C�X�̐����擾
void MIDI_IN::SearchDevNum(void)
{
	devNum = midiInGetNumDevs();
}

// �ڑ��ς݂�MIDI�f�o�C�X�̐��\���i�[
void MIDI_IN::SetMidiCaps(void)
{
	caps.resize(devNum);
	for (UINT i = 0; i < devNum; ++i)
	{
		result = midiInGetDevCaps(i, &caps[i], sizeof(MIDIINCAPS));
		if (result != MMSYSERR_NOERROR)
		{
			Error("�L���v�`���[���s");
		}
		else
		{
			printf("[%d]\n", i + 1);
			printf("      manufacturer ID : %d\n" , caps[i].wMid);
			printf("           product ID : %d\n" , caps[i].wPid);
			printf("version of the driver : %d\n" , caps[i].vDriverVersion);
			printf("         product name : %ls\n", caps[i].szPname);
		}
	}
}

// �R�[���o�b�N�֐�
void MIDI_IN::MidiInProc(HMIDIIN handle, UINT msg, DWORD instance, DWORD param1, DWORD param2)
{
	printf("MidiInProc: msg=%08X, p1=%08X, p2=%08X\n", msg, param1, param2);

	switch (msg)
	{
	case MIM_OPEN:
		printf("MIDI���̓f�o�C�X���J���ꂽ�Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_CLOSE:
		printf("MIDI���̓f�o�C�X������ꂽ�Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_DATA:
		//�X�e�[�^�X�o�C�g
		state = param1 & 0x000000ff;
		if (state == 0xfe)
		{
			printf("�A�N�e�B�u�Z���V���O\n");
		}
		if (state == 0x90)
		{
			printf("�m�[�g�I�����b�Z�[�W\n");

			//�m�[�g�ԍ�
			note = (param1 & 0x0000ff00) >> 8;

			//�x���V�e�B�[
			vel = static_cast<UCHAR>((param1 & 0x00ff0000) >> 16);
			if (vel == 0)
			{
				printf("������ĂȂ�\n");
			}

			printf("�m�[�g�ԍ��F%u, �x���V�e�B�[�F%u\n", note, vel);
		}

		printf("MIDI���b�Z�[�W����M�����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_LONGDATA:
		hdr = (MIDIHDR*)param1;
		for (UINT i = 0; i < hdr->dwBytesRecorded; ++i)
		{
			//�o�C�g���Ƃ�16�i���ŕ\��
			printf("%02X \n", (unsigned char)((hdr->lpData)[i]));
		}

		//�ēx�o�b�t�@���������ēo�^
		midiInPrepareHeader(handle, hdr, sizeof(MIDIHDR));
		midiInAddBuffer(handle, hdr, sizeof(MIDIHDR));

		printf("SysEx�p�o�b�t�@�����܂�A�v���P�[�V�����ɕԂ����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_ERROR:
		printf("������MIDI���b�Z�[�W����M�����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_LONGERROR:
		printf("�����܂��͕s���S��SysEx����M�����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_MOREDATA:
		printf("MIDI���b�Z�[�W����M�������A�v���P�[�V������MIM_DATA������������Ă��Ȃ��ꍇ�ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����B�����Open�֐��̌Ăяo������MIDI_IO_STATUS���w�肳�ꂽ�ꍇ�ɂ̂݌Ăяo�����\n");
		break;
	default:
		break;
	}
}

// MIDI���̓f�o�C�X�̃I�[�v��
bool MIDI_IN::Open(UINT index)
{
	if (devNum <= index)
	{
		return false;
	}

	//�I�[�v��
	result = midiInOpen(&handle, index, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);
	if (result != MMSYSERR_NOERROR)
	{
		Error("MIDI�f�o�C�X�̃I�[�v�����s");
		return false;
	}

	if (SetSysExBuffer() == false)
	{
		return false;
	}

	if (Start() == false)
	{
		return  false;
	}

	return true;
}

// SysEx�̃o�b�t�@�o�^
bool MIDI_IN::SetSysExBuffer(void)
{
	header.lpData = new char[BUFFER_SIZE];
	header.dwBufferLength = BUFFER_SIZE;
	header.dwFlags = 0;

	result = midiInPrepareHeader(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("SysEx�̃Z�b�g���s");
		return false;
	}

	result = midiInAddBuffer(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("SysEx�̒ǉ����s");
		return false;
	}

	return true;
}

// �w�肵��MIDI�f�o�C�X�ł̓��͂̊J�n
bool MIDI_IN::Start(void)
{
	result = midiInStart(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���͊J�n�̎��s");
		return false;
	}

	return true;
}

// �w�肵��MIDI�f�o�C�X�ł̓��͂̏I��
bool MIDI_IN::Stop(void)
{
	result = midiInStop(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���͏I���̎��s");
		return false;
	}

	return true;
}

// �w�肵��MIDI�f�o�C�X�ł̓��͂̒�~
bool MIDI_IN::MidiReset(void)
{
	result = midiInReset(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���Z�b�g���s");
		return false;
	}

	return true;
}

// SysEx�o�b�t�@�̃N���[���A�b�v
bool MIDI_IN::ClearHdr(void)
{
	result = midiInUnprepareHeader(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("SysEx�̃N���[���A�b�v���s");
		return false;
	}

	delete header.lpData;

	return true;
}

// MIDI���̓f�o�C�X�̃N���[�Y
bool MIDI_IN::Close(void)
{
	result = midiInClose(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("�N���[�Y���s");
		return false;
	}

	return true;
}

// ���Z�b�g
void MIDI_IN::Reset(void)
{
	caps.clear();
}


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
void MIDI_OUT::Error(std::string m)
{
	LPWSTR errmsg = 0;
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
