#pragma once
#include "../etc/Vector2.h"
#include "../etc/Typedef.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>

class ImageMane;

class Obj
{
	// ダメージ
	struct Dmg {
		//ダメージ値
		std::ostringstream num;
		//座標
		Vec2 pos;
	};

public:
	// コンストラクタ
	Obj(const std::string& id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2& pos, const bool& reverse);
	// デストラクタ
	~Obj();

	// ステータスのセット
	void SetState(const State& state);

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

	// IDの取得
	std::string GetID(void) {
		std::string id = this->id.substr(0, this->id.find_last_of('.'));
		return id;
	}

	// 座標の取得
	Vec2 GetPos(void) const {
		return pos;
	}
	// 座標のセット
	void SetPos(const Vec2& pos) {
		this->pos = pos;
	}

	// サイズの取得
	Vec2 GetSize(void) const {
		return size * large;
	}
	// サイズのセット
	void SetSize(const Vec2& size) {
		this->size = size;
	}

	// 拡大率の取得
	int GetLarge(void) const {
		return large;
	}
	// 拡大率のセット
	void SetLarge(const int& large) {
		this->large = large;
	}

	// ステータスの取得
	State GetState(void) const {
		return state;
	}

	// 次のステータスの取得
	State GetNextState(void) const {
		return next;
	}
	// 次のステータスのセット
	void SetnextState(const State& state) {
		next = state;
	}

	// 待機時間の取得
	float GetMove(void) const {
		return move;
	}
	// 待機時間のセット
	void SetMove(const float& i) {
		this->move = i;
	}

	// ターゲットの取得
	int GetTarget(void) const {
		return target;
	}
	// ターゲットのセット
	void SetTarget(const int& target) {
		this->target = target;
	}

	// 死亡フラグの取得
	bool GetDie(void) const {
		return die;
	}

	// 攻撃フラグの取得
	bool GetAttackFlag(void) const {
		return attackFlag;
	}
	// 攻撃フラグのセット
	void SetAttackFlag(const bool& flag) {
		this->attackFlag = flag;
	}

	// 体力の取得
	int Gethp(void) const {
		return hp;
	}
	// 体力のセット
	void SetHp(const int& hp) {
		this->hp = hp;
	}
	// 体力の減少
	void Decrease(const int& i) {
		if (tmpDef - i < 0)
		{
			old_hp = this->hp;
			this->hp += tmpDef - i;
		}
	}

	// 攻撃値の取得
	int GetAttack(void) const {
		return attack;
	}
	// 攻撃値のセット
	void SetAttack(const int& attack) {
		this->attack = attack;
	}

	// 防御値の取得
	int GetDef(void) const {
		return def;
	}
	// 防御値のセット
	void SetDef(const int& def) {
		this->def = def;
	}

	// 素早さの取得
	float GetSpeed(void) const {
		return speed;
	}
	// 素早さのセット
	void SetSpeed(const float& speed) {
		this->speed = speed;
	}

private:
	// アニメーションのセット
	void SetAnim(void);

	// アニメーションが終わるかのチェック
	bool AnimEnd(void);

	// アニメーション管理
	void  Animetor(void);

	// 待機時の処理
	void Go(void);

	// 攻撃時の処理
	void Attack1(void);

	// 詠唱待機の処理
	void MasicSet(void);

	// 勝利時の処理
	void Win(void);

	// 防御時の処理
	void Gurd(void);

	// アイテム時の処理
	void Item(void);

	// ダメージ時の処理
	void Damage(void);

	// 死亡時の処理
	void Die(void);


	// イメージマネ
	ImageMane& mane;

	// ID
	std::string id;

	// 画像データ
	int image;

	// 座標
	Vec2 pos; 

	// サイズ
	Vec2 size;

	// アニメーションインデックス
	unsigned int index;

	// アニメーションフレーム
	int flam;

	// 拡大率
	int large;

	// ステータス
	State state;

	// 次のステータス
	State next;

	// 反転フラグ
	bool reverse;

	// アニメーションデータ
	std::map<State, std::vector<int>>anim;

	// 行動開始までの待機時間
	float move;

	// ターゲットインデックス
	int target;

	// 死亡フラグ
	bool die;

	// サークル画像
	int circle;

	// 攻撃フラグ
	bool attackFlag;

	// 体力
	int hp;

	// 攻撃値
	int attack;

	// 防御値
	int def;

	// 素早さ
	float speed;

	// 現在の防御値
	int tmpDef;

	// 前の体力値
	int old_hp;

	// ダメージフレーム
	int damageFlam;

	// ダメージ
	Dmg damage;

	// 関数ポインタ
	void (Obj::*func)(void);
};

