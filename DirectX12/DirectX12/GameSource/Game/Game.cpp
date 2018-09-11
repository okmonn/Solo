#include "Game.h"
#include "../Scene/Title/Title.h"
#include "../../Source/Func/Func.h"
using namespace func;

// �R���X�g���N�^
Game::Game() : 
	winSize({ 640, 480 })
{
}

// �f�X�g���N�^
Game::~Game()
{
}

// �V�[���̈ڍs
void Game::ChangeScene(Scene * scene)
{
	this->scene.reset(scene);
}

// �N���X�̃C���X�^���X
void Game::Init(void)
{
	SetWindowSize(winSize.x, winSize.y);

	func::Init();

	ChangeScene(new Title());
}

// ����
void Game::Run(void)
{
	Init();

	while (CheckMsg() == true && CheckKey(INPUT_ESCAPE) != true)
	{
		Set();

		scene->UpData();
		scene->Draw();

		Do();
	}

	End();
}

// �I������
void Game::End(void)
{
}
