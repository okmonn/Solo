#include "Select.h"
#include "../Game.h"
#include "../../Func.h"
using namespace func;

// �R���X�g���N�^
Select::Select()
{
	fileName.clear();
	func = (GetMidiDevNum() == 0) ? &Select::Key : &Select::Midi;

	std::vector<std::string>m = GetDirFile(".");
}

// �f�X�g���N�^
Select::~Select()
{
}

// �`��
void Select::Draw(void)
{
}

// �L�[����
void Select::Key(void)
{
}

// MIDI����
void Select::Midi(void)
{
}

// ����
void Select::UpData(void)
{
	(this->*func)();
}

