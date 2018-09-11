#pragma once
#include "../../Source/etc/Vector2.h"
#include <map>
#include <string>

// フェード速度
#define FADE_SPEED 0.01f;

class Scene
{
	// データ
	struct Data {
		//画像データ
		unsigned int id;
		//座標
		Vec2f pos;
		//サイズ
		Vec2f size;
		//拡大率
		float large;
	};

public:
	// コンストラクタ
	Scene();
	// デストラクタ
	virtual ~Scene();

	// 描画
	virtual void Draw(void) = 0;
	// 処理
	virtual void UpData(void) = 0;

protected:
	// 画像データの追加
	void AddImg(const std::string& fileName, const Vec2f& size, const Vec2f& pos = 0.0f, float large = 1.0f);

	// 描画
	void Draw(const std::string& name, bool turnX = false, bool turnY = false);

	// 画像消去
	void Delete(const std::string& name);


	// 画像データ
	std::map<std::string, Data>data;

	// アルファ値
	float alpha;
};
