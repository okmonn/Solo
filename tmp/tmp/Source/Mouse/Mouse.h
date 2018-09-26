#pragma once
#include "../etc/Vector2.h"

class Game;

class Mouse
{
public:
	// デストラクタ
	~Mouse();

	// インスタンス変数の取得

	static Mouse& Get(void) {
		static Mouse instance;
		return instance;
	}

	// 処理
	void UpData(void);

	// 左クリック
	bool Click(void) {
		return (state != 0);
	}

	// 左トリガークリック
	bool TrigerClick(void) {
		return (state != 0 && old_state == 0);
	}

	// 座標の取得
	Vec2 GetPos(void) const {
		return pos;
	}

private:
	// コンストラクタ
	Mouse();
	Mouse(const Mouse&) {
	}
	void operator=(const Mouse&) {
	}


	// 座標
	Vec2 pos;

	// 現在の状態
	int state;

	// 過去の状態
	int old_state;
};
