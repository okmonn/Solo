#include "Title.h"
#include "../Game.h"
#include "Select.h"
#include "../../Func.h"
using namespace func;

// �R���X�g���N�^
Title::Title()
{
	func = (GetMidiDevNum() == 0) ? &Title::Key : &Title::Midi;
}

// �f�X�g���N�^
Title::~Title()
{
}

// �`��
void Title::Draw(void)
{
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
}
