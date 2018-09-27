#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <map>

class Obj;

class GameMane
{
public:
	// デストラクタ
	~GameMane();

	// インスタンス変数の取得
	static GameMane& Get(void) {
		static GameMane instance;
		return instance;
	}

	// IDのセット
	void SetID_PL(int index, const std::string& id);
	// IDのセット
	void SetID_EN(int index, const std::string& id);

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);
	
	// クリア
	void Clear(void);

	// プレイヤーキャラの取得
	std::list<std::shared_ptr<Obj>> GetPL(void) {
		return pl;
	}
	// プレイヤーキャラの取得
	std::shared_ptr<Obj> GetPL(int index);

	//	敵キャラの取得
	std::list<std::shared_ptr<Obj>> GetEn(void) {
		return enemy;
	}
	// 敵キャラの取得
	std::shared_ptr<Obj> GetEn(int index);

	// キャラIDの取得
	std::vector<std::string> GetID(void) const {
		return id;
	}
	std::string GetID(int i) const {
		return id[i];
	}

private:
	// コンストラクタ
	GameMane();
	GameMane(const GameMane&) {
	}
	void operator=(const GameMane&) {
	}


	// プレイヤーキャラの生成
	void CreatePl(const std::string& id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2& pos = 0, const bool& reverse = true);
	// 敵キャラの生成
	void CreateEnemy(const std::string& id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2& pos = 0, const bool& reverse = false);

	// キャラの生成
	void CreateObj(void);

	// 描画
	void Draw(const std::list<std::shared_ptr<Obj>>& list);

	// 処理
	void UpData(std::list<std::shared_ptr<Obj>>& list);


	// キャラID
	std::vector<std::string>plID;

	// 敵ID
	std::vector<std::string>enID;

	// プレイヤーキャラ
	std::list<std::shared_ptr<Obj>>pl;

	// 敵キャラ
	std::list<std::shared_ptr<Obj>>enemy;

	// キャラIDリスト
	std::vector<std::string>id;
};

