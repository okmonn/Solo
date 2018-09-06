#include "Game.h"
#include "Scene/Title.h"
#include"../Func.h"
using namespace func;

//ウィンドウサイズ
const Vec2 winSize = { 640U, 480U };

// コンストラクタ
Game::Game()
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
