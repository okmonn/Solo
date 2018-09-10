#include "MIDI_IN.h"

#pragma comment(lib, "winmm.lib")

// �o�b�t�@�[�T�C�Y
#define BUFFER_SIZE 256

//���K
static const char keys[] = "CDEFGAB";

UCHAR MIDI_IN::state = 0;
UCHAR MIDI_IN::data1 = 0;
UCHAR MIDI_IN::data2 = 0;

// �R���X�g���N�^
MIDI_IN::MIDI_IN() :
	result(S_OK), handle(nullptr), devNum(midiInGetNumDevs())
{
	header = {};
	caps.clear();

	if (devNum > 0)
	{
		SetMidiCaps();
		Open();
		Prepare();
		Start();
	}
}

// �f�X�g���N�^
MIDI_IN::~MIDI_IN()
{
	if (devNum > 0)
	{
		Stop();
		Reset();
		UnPrepare();
		Close();

		delete header.lpData;
	}
}

// MIDI���b�Z�[�W�̊m�F
void MIDI_IN::MimData(DWORD param1, DWORD param2)
{
	//��M�f�[�^�̕���
	state = param1 & 0xff;
	data1 = param1 >> 8 & 0xff;
	data2 = param1 >> 16 & 0xff;

	//�^�C�~���O�N���b�N���b�Z�[�W�͖���
	if (state == 0xf8)
	{
		return;
	}
	
	//��M�f�[�^�̕\��
	printf("%10.3f  %02X %02X %02X : ", (double)param2 / 1000, state, data1, data2);

	if (state >> 4 == 0xf) 
	{
		//�V�X�e�� ���b�Z�[�W
		switch (state & 0xf)
		{
		case 0x1:
			printf("MTC�N�H�[�^�[�t���[�� (Type:%d Val:%2d)\n", data1 >> 4 & 0xf, data1 & 0xf);
			break;
		case 0x2:
			printf("�\���O�|�W�V�����|�C���^ (Beat:%5d)\n", (data1 + data2) << 7);
			break;
		case 0x3:
			printf("�\���O�Z���N�g (Num:%3d)\n", data1);
			break;
		case 0x6:
			printf("�`���[�����N�G�X�g\n");
			break;
		case 0x7:
			printf("�G���h�I�u�G�N�X�N���[�V�u\n");
			break;
		case 0x8:
			printf("�^�C�~���O�N���b�N\n");
			break;
		case 0xA:
			printf("�X�^�[�g\n");
			break;
		case 0xB:
			printf("�R���e�B�j���[\n");
			break;
		case 0xC:
			printf("�X�g�b�v\n");
			break;
		case 0xE:
			printf("�A�N�e�B�u�Z���V���O\n");
			break;
		case 0xF:
			printf("�V�X�e�����Z�b�g\n");
			break;
		default:
			printf("�s���ȃ��b�Z�[�W\n");
			break;
		}
	}
	else
	{
		printf("[%2dch] ", (state & 0xf) + 1);

		//�`���l�� ���b�Z�[�W
		switch (state >> 4) 
		{
		case 0x8:
			printf("�m�[�g�I�t (Note:%c%-2d Vel:%3d)\n", keys[data1 % 7], data1 / 7 - 3, data2);
			break;
		case 0x9:
			printf("�m�[�g�I�� %s (Note:%c%-2d Vel:%3d)\n", (data2 ? "on " : "off"), keys[data1 % 7], data1 / 7 - 3, data2);
			break;
		case 0xa:
			printf("�|���t�H�j�b�N�L�[�v���b�V���[ (Note:%c%-2d Prss:%3d)\n", keys[data1 % 7], data1 / 7 - 3, data2);
			break;
		case 0xb:
			printf("�R���g���[���`�F���W (Num:%3d Val:%3d)\n", data1, data2);
			break;
		case 0xc:
			printf("�v���O�����`�F���W (Num:%3d)\n", data1);
			break;
		case 0xd:
			printf("�`�����l���v���b�V���[ (Prss:%3d)\n", data1);
			break;
		case 0xe:
			printf("�s�b�`�x���h�`�F���W (Val:%5d)\n", (data1 + data2) << 7);
			break;
		default:
			printf("�s���ȃ��b�Z�[�W\n");
			break;
		}
	}
}

// �R�[���o�b�N�֐�
void MIDI_IN::MidiInProc(HMIDIIN handle, UINT msg, DWORD instance, DWORD param1, DWORD param2)
{
	MIDIHDR *hdr = (MIDIHDR*)param1;

	switch (msg)
	{
	case MIM_OPEN:
		printf("MIDI���̓f�o�C�X���J���ꂽ�Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_CLOSE:
		printf("MIDI���̓f�o�C�X������ꂽ�Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_DATA:
		printf("MIDI���b�Z�[�W����M�����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		MimData(param1, param2);
		break;
	case MIM_LONGDATA:
		printf("SysEx�p�o�b�t�@�����܂�A�v���P�[�V�����ɕԂ����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_ERROR:
		printf("������MIDI���b�Z�[�W����M�����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");
		break;
	case MIM_LONGERROR:
		printf("�����܂��͕s���S��SysEx����M�����Ƃ��ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����\n");

		//�ēx�o�b�t�@���������ēo�^
		midiInPrepareHeader(handle, hdr, sizeof(MIDIHDR));
		midiInAddBuffer(handle, hdr, sizeof(MIDIHDR));
		break;
	case MIM_MOREDATA:
		printf("MIDI���b�Z�[�W����M�������A�v���P�[�V������MIM_DATA������������Ă��Ȃ��ꍇ�ɂ��̒l���ݒ肳��ăR�[���o�b�N�֐����Ăяo�����B�����Open�֐��̌Ăяo������MIDI_IO_STATUS���w�肳�ꂽ�ꍇ�ɂ̂݌Ăяo�����\n");
		break;
	default:
		break;
	}
}

// �G���[���b�Z�[�W
void MIDI_IN::Error(const std::string& m)
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

// �ڑ��ς݂�MIDI�f�o�C�X�̐��\���i�[
void MIDI_IN::SetMidiCaps(void)
{
	//�z��̃������m��
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
			printf("���[�J�[ID          �F%d\n", caps[i].wMid);
			printf("���iID              �F%d\n", caps[i].wPid);
			printf("�h���C�o�̃o�[�W�����F%d\n", caps[i].vDriverVersion);
			printf("���i��              �F%ls\n", caps[i].szPname);
		}
	}
}

// MIDI���̓f�o�C�X�̃I�[�v��
HRESULT MIDI_IN::Open(UINT index)
{
	result = midiInOpen(&handle, index, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);
	if (result != MMSYSERR_NOERROR)
	{
		Error("MIDI�f�o�C�X�̃I�[�v�����s");
	}

	return result;
}

// �V�X�e���G�N�X�N���[�V�u�̒ǉ�
HRESULT MIDI_IN::Prepare(void)
{
	header.lpData         = new char[BUFFER_SIZE];
	header.dwBufferLength = BUFFER_SIZE;
	header.dwFlags        = 0;

	result = midiInPrepareHeader(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("�V�X�e���G�N�X�N���[�V�u�̏������s");
		return result;
	}

	result = midiInAddBuffer(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("�V�X�e���G�N�X�N���[�V�u�̒ǉ����s");
	}

	return result;
}

// MIDI�f�o�C�X�̓��͊J�n
HRESULT MIDI_IN::Start(void)
{
	result = midiInStart(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���͊J�n�̎��s");
	}

	return result;
}

// MIDI�f�o�C�X�̓��͒�~
HRESULT MIDI_IN::Stop(void)
{
	result = midiInStop(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���͒�~�̎��s");
	}

	return result;
}

// MIDI�f�o�C�X�̃��Z�b�g
HRESULT MIDI_IN::Reset(void)
{
	result = midiInReset(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("���Z�b�g�̎��s");
	}

	return result;
}

// �V�X�e���G�N�X�N���[�V�u�̃N���[���A�b�v
HRESULT MIDI_IN::UnPrepare(void)
{
	result = midiInUnprepareHeader(handle, &header, sizeof(MIDIHDR));
	if (result != MMSYSERR_NOERROR)
	{
		Error("�N���[���A�b�v�̎��s");
	}

	return result;
}

// MIDI�f�o�C�X�̓��͏I��
HRESULT MIDI_IN::Close(void)
{
	result = midiInClose(handle);
	if (result != MMSYSERR_NOERROR)
	{
		Error("�N���[�Y���s");
	}

	return result;
}
