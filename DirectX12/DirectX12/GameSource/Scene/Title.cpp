#include "Title.h"
#include "../Game.h"
#include "Select.h"
#include "../etc/Share.h"
#include "../../Func.h"
using namespace func;

// �R���X�g���N�^
Title::Title()
{
	func = (GetMidiDevNum() == 0) ? &Title::Key : &Title::Midi;

	Load();
}

// �f�X�g���N�^
Title::~Title()
{
}

// �摜�ǂݍ���
void Title::Load(void)
{
	AddImg("Materials/img/TitleName.png");
}

// �`��
void Title::Draw(void)
{
	Scene::Draw("TitleName", { 0.0f, 0.0f }, { (float)Game::Get().GetWinSize().x, (float)Game::Get().GetWinSize().y });
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
