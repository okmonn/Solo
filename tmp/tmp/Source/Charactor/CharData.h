#pragma once
#include <string>
#include <map>

// キャラデータ
struct Data {
	//体力
	int hp;
	//攻撃
	int attack;
	//防御
	int def;
	//すばやさ
	float speed;
};

// キャラ一覧
std::map<std::string, Data> charData {
	{ "1054010303", { 100, 100, 10, 0.1f } },
	{ "1055010303", { 100, 100, 10, 0.5f } },
};
