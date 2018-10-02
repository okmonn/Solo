#pragma once
#include <string>
#include <map>

// キャラデータ
struct CharData {
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
std::map<std::string, CharData> charData {
	{ "1001010303", { 100,  5,  5, 1.0f } },
	{ "1007010303", { 100, 15, 10, 0.7f } },
	{ "1008010303", { 100,  8,  5, 0.8f } },
	{ "1011010303", { 100, 25, 25, 0.2f } },
	{ "1054010303", { 100,  3,  5, 1.2f } },
	{ "1055010303", { 100, 10, 10, 0.7f } },
};
