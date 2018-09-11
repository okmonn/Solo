#include "Game.h"
#include "../Scene/Title/Title.h"
#include "../../Source/Func/Func.h"
using namespace func;

// コンストラクタ
Game::Game() : 
	winSize({ 640, 480 })
{
}

// デストラクタ
Game::~Game()
{
}

// シーンの移行
void Game::ChangeScene(Scene * scene)
{
	this->scene.reset(scene);
}

// クラスのインスタンス
void Game::Init(void)
{
	SetWindowSize(winSize.x, winSize.y);

	func::Init();

	ChangeScene(new Title());
}

// 処理
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

// 終了処理
void Game::End(void)
{
}
