#pragma once
#include "../../etc/Vector2.h"
#include <vector>

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
