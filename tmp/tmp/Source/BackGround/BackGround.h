#pragma once
#include "../etc/Vector2.h"

class BackGround
{
public:
	// コンストラクタ
	BackGround();
	// デストラクタ
	~BackGround();

	// 描画
	void Draw(void);

	// 座標の取得
	Vec2 GetPos(void) const {
		return pos;
	}
	// 座標のセット
	void SetPos(const Vec2& pos) {
		this->pos = pos;
	}

	// サイズの取得
	Vec2 GetSize(void) const {
		return size;
	}
	// サイズのセット
	void SetSize(const Vec2& size) {
		this->size = size;
	}

private:
	// 画像
	int image;

	// 座標
	Vec2 pos;

	// サイズ
	Vec2 size;
};

