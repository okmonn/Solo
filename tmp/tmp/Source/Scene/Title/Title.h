#pragma once
#include "../Scene.h"
#include <vector>

class Mouse;

class Title :
	public Scene
{
	struct Circle {
		//座標
		Vec2 pos;
		//半径
		int radius;
		//色
		unsigned int color;
		//出現フラグ
		bool flag;
	};

public:
	// コンストラクタ
	Title();
	// デストラクタ
	~Title();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 円の初期化
	void CircleInit(void);

	// フェードイン
	void FadeIn(void);

	// 通常処理
	void Normal(void);

	// フェードアウト
	void FadeOut(void);


	// マウス
	Mouse& mouse;

	// 円
	std::vector<Circle>circle;

	// 関数ポインタ
	void (Title::*func)(void);
};

