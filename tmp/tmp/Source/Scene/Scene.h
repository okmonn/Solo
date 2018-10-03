#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <map>

class Game;
class ImageMane;

class Scene
{
	// 画像データ
	struct Data {
		int image;
		Vec2 size;
		Vec2 pos;
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
	// 画像の読み込み
	void Load(const std::string& fileName, const std::string& name, const Vec2& size, const Vec2& pos = 0);

	// 描画
	int DrawGraph(const std::string& name);

	// 描画・自由変形
	int DrawModiGraph(const std::string& name);


	// ゲーム
	Game& game;

	// イメージマネージャー
	ImageMane& mane;

	// アルファ値
	int alpha;

	// フェード速度
	int fadeSpeed;

	// 画像データ
	std::map<std::string, Data>image;
};

