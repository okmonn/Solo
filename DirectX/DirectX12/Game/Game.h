#pragma once
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

	// シーンの移行
	void ChangeScene(Scene* scene);

	// 処理
	void Run(void);

private:
	// コンストラクタ
	Game();
	Game(const Game&) {
	}
	void operator=(const Game&) {
	}

	// クラスのインスタンス
	void Init(void);

	// 終了処理
	void End(void);


	// シーン
	std::shared_ptr<Scene>scene;
};
