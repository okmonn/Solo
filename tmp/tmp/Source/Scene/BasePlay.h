#pragma once
#include "Scene.h"
#include <vector>
#include <memory>

class Game;
class GameMane;
class Mouse;
class Stage;
class BackGround;

class BasePlay :
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

public:
	// コンストラクタ
	BasePlay();
	// デストラクタ
	virtual ~BasePlay();

	// 描画
	virtual void Draw(void) = 0;

	// 処理
	virtual void UpData(void) = 0;

protected:
	// コマンドのセット
	void SetCom(int index, const std::string name, const Vec2& pos = 0, const Vec2& size = 0);

	// コマンドの初期化
	void ComInit(void);

	// 敵の読み込み
	void LoadEnemy(void);

	// 戦闘前の描画
	void SetDraw(void);

	// 戦闘時の処理
	void ButtleDraw(void);

	// 戦闘終了時の処理
	void EndDraw(void);

	// コマンドの処理
	void ComUpData(void);

	// ターゲットのセット
	void SetTarget(void);

	// 選択キャラのセット
	void SetSelect(void);

	// プレイヤーキャラの攻撃
	void Attack_PL(void);

	// 敵キャラの攻撃
	void Attack_EN(void);

	// 戦闘時の処理
	void ButtleUpData(void);

	// 戦闘終了時の処理
	void EndUpData(void);


	// ゲーム
	Game& game;

	// ゲームマネ
	GameMane& mane;

	// マウス
	Mouse& mouse;

	// ステージ
	Stage& stage;

	// 背景
	std::shared_ptr<BackGround> back;

	// 選択中のキャラ
	int select;

	// ターゲット
	int target;

	// 経過時間
	int flam;

	// コマンド
	std::vector<Command>com;
};

