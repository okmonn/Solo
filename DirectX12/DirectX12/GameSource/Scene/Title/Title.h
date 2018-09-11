#pragma once
#include "../Scene.h"

class Title :
	public Scene
{
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
	// 画像読み込み
	void Load(void);

	// フェードイン
	void FadeIn(void);

	// フェードアウト
	void FadeOut(void);

	// 通常描画
	void NormalDraw(void);

	// キー入力
	void Key(void);

	// MIDI入力
	void Midi(void);


	// フレーム
	unsigned int flam;

	// 関数ポインタ
	void (Title::*draw)(void);
	void (Title::*updata)(void);
};

