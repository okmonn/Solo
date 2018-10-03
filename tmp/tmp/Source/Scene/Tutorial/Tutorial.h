#pragma once
#include "../BasePlay.h"

class Tutorial :
	public BasePlay
{
public:
	// コンストラクタ
	Tutorial();
	// デストラクタ
	~Tutorial();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// プレイヤーの読み込み
	void LoadPlayer(void);

	// 説明文字の表示
	void DrawString(const std::string& mozi);

	// フェードイン
	void FadeIn(void);
	
	// 戦闘前処理
	void SetUpData(void);

	// 自陣と敵陣の説明
	void Description1(void);
	

	// 吹き出し座標
	Vec2 pos;

	// 吹き出しサイズ
	Vec2 size;

	// 進行状況カウント
	unsigned int cnt;

	// 経過フレーム
	unsigned int flam;

	// インデックス
	int index;

	// 吹き出しインデックス
	int num;

	// 表示文字
	std::vector<std::string> st;

	// 色
	unsigned int color;

	// 関数ポインタ
	void (Tutorial::*draw)(void);
	void (Tutorial::*updata)(void);
};

