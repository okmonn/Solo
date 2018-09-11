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

	// キー入力
	void Key(void);

	// MIDI入力
	void Midi(void);


	// 関数ポインタ
	void (Title::*func)(void);
};

