#pragma once
#include "../../etc/Vector2.h"
#include <vector>

// Ç©Ç¡Ç±ç¿ïW
struct Parenthesis {
	//ç∂
	Vec2 left;
	//âE
	Vec2 right;
};

// Ç©Ç¡Ç±ÇÃç¿ïW
const std::vector<Parenthesis>par = {
	{{0, 0}, {640 / 4, 480}},
	{{640 - 640 / 4, 0}, {640, 480}},
	{{0, 0}, {120, 60}}
};
