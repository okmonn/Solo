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
	{{0, 0}, {120, 60}}
};
