#pragma once
#include "../../etc/Vector2.h"
#include <vector>

// 最大文字数
#define MOZI_MAX 11

// 最大行数
#define MAX 3

// かっこ座標
struct Parenthesis {
	//左
	Vec2 left;
	//右
	Vec2 right;
};

// かっこの座標
const std::vector<Parenthesis>par = {
	{{0, 0}, {640 / 4, 480}},
	{{640 - 640 / 4, 0}, {640, 480}},
	{{190, 195}, {310, 255}},
	{{340, 195}, {460, 255}},
	{{190, 295}, {310, 355}},
	{{340, 295}, {460, 355}},
};

// 吹き出し文字列
const std::vector<std::string>m = {
	"こちら自陣",
	"こちら敵陣",
	"攻撃コマンドは敵に攻撃命令をだします",
	"防御コマンドは攻撃を受けるまで防御をあげます",
	"構えるコマンドは次の攻撃ダメージを上げます",
	"回復コマンドは自分の体力を回復させます"
};
