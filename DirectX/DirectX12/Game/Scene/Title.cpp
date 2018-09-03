#include "Title.h"
#include "../Game.h"
#include "Select.h"
#include "../../Func.h"
using namespace func;
#include <stdio.h>

UINT n = 0;
UINT a = 0;

// �R���X�g���N�^
Title::Title()
{
	func = (GetMidiDevNum() == 0) ? &Title::Key : &Title::Midi;
	LoadImg(n, "img/sample.png");
	LoadWave(a, "wave/sample1.wav");
}

// �f�X�g���N�^
Title::~Title()
{
}

// �`��
void Title::Draw(void)
{
	func::Draw(n, 0, 0);
}

// �L�[����
void Title::Key(void)
{
	if (TriggerKey(INPUT_RETURN))
	{
		Game::Get().ChangeScene(new Select());
	}
}

// MIDI����
void Title::Midi(void)
{

}

// ����
void Title::UpData(void)
{
	(this->*func)();
	PlayWave(a);
}
