#pragma once
#include "../../Source/etc/Vector2.h"

class BaseObj
{
public:
	// コンストラクタ
	BaseObj();
	// デストラクタ
	virtual ~BaseObj();

	// 座標の取得
	Vec2f GetPos(void) const {
		return pos;
	}
	// 座標のセット
	void SetPos(const Vec2f& pos) {
		this->pos = pos;
	}

	// サイズの取得
	Vec2f GetSize(void) const {
		return size;
	}
	// サイズのセット
	void SetSize(const Vec2f& size) {
		this->size = size;
	}

	// 拡大率の取得
	float GetLarge(void) const {
		return large;
	}
	// 拡大率のセット
	void SetLarge(float large) {
		this->large = large;
	}

protected:
	// 座標
	Vec2f pos;

	// サイズ
	Vec2f size;

	// 拡大率
	float large;
};

