#include "Title.h"
#include "../../Game/Game.h"
#include "../Select/Select.h"
#include "../../etc/Share.h"
#include "../../../Source/Func/Func.h"
using namespace func;

// �R���X�g���N�^
Title::Title()
{
	func = (GetMidiDevNum() <= 0) ? &Title::Key : &Title::Midi;

	Load();
}

// �f�X�g���N�^
Title::~Title()
{
}

// �摜�ǂݍ���
void Title::Load(void)
{
	AddImg("Material/img/TitleName.png");
}

// �`��
void Title::Draw(void)
{
	Scene::Draw("TitleName", { 0.0f, 0.0f }, { (float)Game::Get().GetWinSize().x, (float)Game::Get().GetWinSize().y });

	static float alpha = 1.0f;
	SetAlpha(alpha);
	DrawBox(0, 0, 640, 480, 0, 0, 0);
	SetAlpha(1.0f);

	alpha -= 0.005f;
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
