#include "Game.h"
#include "Scene/Title.h"
#include"../Func.h"
using namespace func;

//�E�B���h�E�T�C�Y
const Vec2 winSize = { 640U, 480U };

// �R���X�g���N�^
Game::Game()
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

	while (CheckMsg() == true && CheckKey(INPUT_ESCAPE) == false)
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
