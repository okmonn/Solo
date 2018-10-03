#pragma once
#include "../Scene.h"
#include <vector>

class Mouse;
class Stage;

class Select :
	public Scene
{
	// クエスト項目情報
	struct QuestName {
		//クエスト名
		std::string name;
		//座標
		Vec2 pos;
		//サイズ
		Vec2 size;
		//オフセット
		Vec2 offset;
		//色
		unsigned int color;
	};

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
	// 画像の読み込み
	void LoadInit(void);

	// クエスト名の初期化
	void QuestInit(void);

	// フェードイン
	void FadeIn(void);

	// 通常処理
	void Normal(void);

	// フェードアウト
	void FadeOut(void);


	// マウス
	Mouse& mouse;

	// ステージ
	Stage& stage;

	// 色
	unsigned int color;

	// クエスト項目
	std::vector<QuestName>quest;

	// 関数ポインタ
	void (Select::*func)(void);
};
