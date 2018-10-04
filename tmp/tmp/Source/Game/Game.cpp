#include "Game.h"
#include "../Icon/Icon.h"
#include "../Scene/Title/Title.h"
#include "../Mouse/Mouse.h"
#include "DxLib.h"

// ウィンドウサイズ
#define WINDOW_X 640
#define WINDOW_Y 480

// コンストラクタ
Game::Game() :
	scene(nullptr), size({ WINDOW_X, WINDOW_Y }) , fontSize(48)
{
}

// デストラクタ
Game::~Game()
{
}

// シーン移行
void Game::ChangeScene(Scene * scene)
{
	this->scene.reset(scene);
}

// 初期化
void Game::Init(void)
{
	//ログの出力制御
	SetOutApplicationLogValidFlag(false);

	//グラフィックモードの設定
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	//true:window　false:ﾌﾙｽｸﾘｰﾝ
	ChangeWindowMode(true);

	// アイコンセット
	SetWindowIconID(ICON_ID);

	//windowテキストの設定
	SetWindowText(_T("1601271_岡繁男"));

	//Dxlibの初期化
	if (DxLib_Init() == -1)
	{
		return;
	}

	// フォント追加
	AddFontResourceEx("Material/font/GN-Kin-iro_SansSerif.ttf", FR_PRIVATE, NULL);
	ChangeFont("GN-きんいろサンセリフ", DX_CHARSET_DEFAULT);
	SetFontSize(fontSize);

	//マウスカーソルの表示
	SetMouseDispFlag(true);

	//ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	SetDrawScreen(DX_SCREEN_BACK);

	//初期シーン
	ChangeScene(new Title());
}

// 描画
void Game::Draw(void)
{
	//画面消去
	ClsDrawScreen();

	scene->Draw();

	//裏画面を表画面に瞬間コピー
	ScreenFlip();
}

// 処理
void Game::UpData(void)
{
	Draw();

	Mouse::Get().UpData();

	scene->UpData();
}


// 処理
void Game::Run(void)
{
	Init();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		UpData();
	}

	End();
}

// 終了処理
void Game::End(void)
{
	DxLib_End();
}
