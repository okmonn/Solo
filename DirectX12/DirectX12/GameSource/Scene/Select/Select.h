#pragma once
#include "../Scene.h"
#include <vector>
#include <string>

class Select :
	public Scene
{
public:
	// コンストラクタ
	Select();
	// デストラクタ
	~Select();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 読み込み
	void Load(void);

	// メルセンヌツイスタ
	void MT(Vec2f& pos, const Vec2f& offset = 0.0f);
	void MT(unsigned int& i, unsigned int min, unsigned int max);

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


	// 楽曲一覧
	std::vector<std::string> song;

	// 描画数
	unsigned int drawCnt;

	// 透過フラグ
	bool flag;

	// 現在のインデックス
	int index;

	// 関数ポインタ
	void (Select::*draw)(void);
	void (Select::*updata)(void);
};

