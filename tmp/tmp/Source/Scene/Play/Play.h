#pragma once
#include "../Scene.h"
#include <vector>
#include <memory>

class GameMane;
class Mouse;
class Stage;
class BackGround;

class Play :
	public Scene
{
	// コマンド
	struct Command {
		//名前
		std::string name;
		//座標
		Vec2 pos;
		//サイズ
		Vec2 size;
		//色
		unsigned int color;
		//オフセット
		Vec2 offset;
	};

	// ダメージ
	struct Damage {
		//ダメージ
		std::ostringstream num;
		//座標
		Vec2 pos;
	};

public:
	// コンストラクタ
	Play();
	// デストラクタ
	~Play();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// コマンドのセット
	void SetCom(int index, const std::string name, const Vec2& pos = 0, const Vec2& size = 0);

	// コマンドの初期化
	void ComInit(void);

	// 敵の読み込み
	void LoadEnemy(void);

	// 戦闘前描画
	void SetDraw(void);

	// 戦闘描画
	void BattleDraw(void);

	// 終了描画
	void EndDraw(void);

	// 戦闘前処理
	void SetUpData(void);

	// 戦闘処理
	void BattleUpData(void);

	// 終了処理
	void EndUpData(void);
	

	// ゲームマネ
	GameMane& mane;

	// マウス
	Mouse& mouse;

	// ステージ
	Stage& stage;

	// 背景
	std::shared_ptr<BackGround>back;

	// 選択中のキャラ
	int select;

	// ターゲット
	int target;

	// 経過時間
	int flam;

	// 戦闘コマンド
	std::vector<Command>com;

	// 関数ポインタ
	void (Play::*draw)(void);
	void (Play::*updata)(void);
};

