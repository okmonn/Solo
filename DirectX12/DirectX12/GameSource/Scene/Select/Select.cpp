#include "Select.h"
#include "../../Game/Game.h"
#include "../../../Source/Func/Func.h"
using namespace func;

// �R���X�g���N�^
Select::Select()
{
	fileName.clear();
	func = (GetMidiDevNum() <= 0) ? &Select::Key : &Select::Midi;

	std::vector<std::wstring>m = GetDirFile(L".");
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

