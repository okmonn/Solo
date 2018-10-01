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

	// 戦闘前処理
	void SetUpData(void);

	// 自陣と敵陣の説明
	void Description1(void);
	

	// 進行状況カウント
	int cnt;

	// 関数ポインタ
	void (Tutorial::*draw)(void);
	void (Tutorial::*updata)(void);
};

