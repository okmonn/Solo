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
	// 選択インデックスの初期化
	void InitSelect(void);

	// 画像読み込み
	void Load(void);

	// フェードイン
	void FadeIn(void);

	// キャラ選択
	void ChooseObj(void);

	// 通常処理
	void Normal(void);

	// フェードアウト
	void FadeOut(void);


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

	// 選択インデックス
	std::vector<unsigned int>select;

	// ターゲット
	int target;

	// キャラサイズ
	Vec2 size;

	// 拡大率
	int large;

	// プレイ移行コマンド座標
	Vec2 playPos;

	// プレイ移行コマンドサイズ
	Vec2 playSize;

	// 色
	unsigned int color;

	// ボックス色
	unsigned int b_color;

	// 画像ハンドル
	std::vector<int>handle;

	// 関数ポインタ
	void (Choose::*func)(void);
};
