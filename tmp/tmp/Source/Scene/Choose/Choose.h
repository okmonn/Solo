#pragma once
#include "../Scene.h"
#include <vector>

class ImageMane;
class GameMane;
class Mouse;

class Choose :
	public Scene
{
public:
	// コンストラクタ
	Choose();
	// デストラクタ
	~Choose();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 画像読み込み
	void Load(void);


	// イメージマネ
	ImageMane& image;

	// ゲームマネ
	GameMane& mane;

	// マウス
	Mouse& mouse;

	// 経過フレーム
	int flam;

	// インデックス
	unsigned int index;

	// 画像ハンドル
	std::vector<int>handle;
};
