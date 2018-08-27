#include "Xaudio2.h"
#define _NOT_USE_D3D12
#include "../DirectX/Obj.h"
#include "WAVE/WAVE.h"
#include <tchar.h>
#include <mutex>

#pragma comment(lib, "xaudio2.lib")

// �R���X�g���N�^
Xaudio2::Xaudio2() :
	result(S_OK), audio(nullptr), master(nullptr)
{
	wave.clear();
	voice.clear();
	th.clear();

	Init();
	CreateAudio();
#ifdef _DEBUG
	SetDebug();
#endif
	CreateMaster();
}

// �f�X�g���N�^
Xaudio2::~Xaudio2()
{
	for (auto itr = wave.begin(); itr != wave.end(); ++itr)
	{
		itr->second.SetEnd(true);
	}
	for (auto itr = voice.begin(); itr != voice.end(); ++itr)
	{
		if (itr->second != nullptr)
		{
			result = itr->second->Stop();
			if (FAILED(result))
			{
				OutputDebugString(_T("\n�Đ��̒�~�F���s\n"));
			}
			itr->second->DestroyVoice();
		}
	}
	if (master != nullptr)
	{
		master->DestroyVoice();
	}
	Release(audio);
	CoUninitialize();
}

// ������
HRESULT Xaudio2::Init(void)
{
	result = CoInitialize(nullptr);
	if (FAILED(result))
	{
		OutputDebugString(_T("\nCOM�̏������F���s\n"));
	}

	return result;
}

// XAudio2�̐���
HRESULT Xaudio2::CreateAudio(void)
{
	result = XAudio2Create(&audio);
	if (FAILED(result))
	{
		OutputDebugString(_T("\nXAudio2�̐����F���s\n"));
	}

	return result;
}

// �f�o�b�O�̃Z�b�g
void Xaudio2::SetDebug(void)
{
	XAUDIO2_DEBUG_CONFIGURATION debug = {};
	debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
	debug.BreakMask = XAUDIO2_LOG_ERRORS;
	audio->SetDebugConfiguration(&debug, 0);
}

// �}�X�^�[�{�C�X�̐���
HRESULT Xaudio2::CreateMaster(void)
{
	result = audio->CreateMasteringVoice(&master);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�}�X�^�[�{�C�X�̐����F���s\n"));
	}

	return result;
}

// �ǂݍ���
HRESULT Xaudio2::LoadWAVE(UINT& index, const std::string& fileName)
{
	wave[&index].Load(fileName);

	result = audio->CreateSourceVoice(&voice[&wave[&index]], &wave[&index].format, 0, 1.0f, &wave[&index].callback);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�\�[�X�{�C�X�̐����F���s\n"));
		return result;
	}

	th[&wave[&index]] = std::thread(&Xaudio2::Start, this, std::ref(index));
	th[&wave[&index]].detach();

	return result;
}

// �ʃX���b�h�œǂݍ���
void Xaudio2::Start(UINT & index)
{
	XAUDIO2_VOICE_STATE state = {};
	while (wave[&index].GetEnd() == false)
	{
		if (wave[&index].GetStart() == false)
		{
			continue;
		}
		voice[&wave[&index]]->GetState(&state);
		if (state.BuffersQueued <= wave[&index].data.size() - 1)
		{
			std::mutex mtx;
			std::lock_guard<std::mutex> lock(mtx);
			wave[&index].Load();

			//�o�b�t�@�[�ݒ�p�\����
			XAUDIO2_BUFFER buffer = {};
			buffer.AudioBytes = wave[&index].data[wave[&index].GetIndex()].size();
			buffer.pAudioData = wave[&index].data[wave[&index].GetIndex()].data();
			buffer.Flags = XAUDIO2_END_OF_STREAM;

			//�o�b�t�@�[�̃Z�b�g
			result = voice[&wave[&index]]->SubmitSourceBuffer(&buffer);
			if (FAILED(result))
			{
				OutputDebugString(_T("\n�o�b�t�@�[�̃Z�b�g�F���s\n"));
			}
		}
	}

	//�L���[�ɉ����͂��Ă�����
	if (state.BuffersQueued > 0)
	{
		state.BuffersQueued = 0;
	}
}

// �Đ��J�n
HRESULT Xaudio2::Play(UINT& index)
{
	//�Đ��J�n
	if (wave[&index].GetStart() == false)
	{
		result = voice[&wave[&index]]->Start();
		if (FAILED(result))
		{
			OutputDebugString(_T("\n�Đ��F���s\n"));
			return result;
		}

		wave[&index].SetStart(true);
	}

	return result;
}

// �Đ���~
HRESULT Xaudio2::Stop(UINT& index)
{
	if (wave[&index].GetStart() == true)
	{
		result = voice[&wave[&index]]->Stop();
		if (FAILED(result))
		{
			OutputDebugString(_T("\n�Đ���~�F���s\n"));
			return result;
		}

		wave[&index].SetStart(false);
	}

	return result;
}

// �\�[�X�{�C�X�̏���
void Xaudio2::Delete(UINT& index)
{
	if (voice[&wave[&index]] != nullptr)
	{
		result = voice[&wave[&index]]->Stop();
		if (FAILED(result))
		{
			OutputDebugString(_T("\n�Đ��̒�~�F���s\n"));
		}
		voice[&wave[&index]]->DestroyVoice();
	}

	for (auto itr = voice.begin(); itr != voice.end();)
	{
		if (itr->first == &wave[&index])
		{
			itr = voice.erase(itr);
			break;
		}
		else
		{
			++itr;
		}
	}
}
