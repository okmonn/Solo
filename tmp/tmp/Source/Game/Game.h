#pragma once
#include "../etc/Vector2.h"
#include <memory>

class Scene;

class Game
{
public:
	// デストラクタ
	~Game();

	// インスタンス変数の取得
	static Game& Get(void) {
		static Game instance;
		return instance;
	}

	// 処理
	void Run(void);

	// シーン移行
	void ChangeScene(Scene* scene);

	// ウィンドウサイズの取得
	Vec2 GetWinSize(void) const {
		return size;
	}

	// フォントサイズの取得
	int GetFontSize(void) const {
		return fontSize;
	}

private:
	// コンストラクタ
	Game();
	Game(const Game&) {
	}
	void operator=(const Game&) {
	}

	// 初期化
	void Init(void);

	// 描画
	void Draw(void); 

	// 処理
	void UpData(void);

	// 終了処理
	void End(void);


	// シーン
	std::shared_ptr<Scene>scene;

	// ウィンドウサイズ
	Vec2 size;

	// フォントサイズ
	int fontSize;
};

