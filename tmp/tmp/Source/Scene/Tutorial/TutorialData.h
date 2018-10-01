#pragma once
#include "../../etc/Vector2.h"
#include <vector>

// ���������W
struct Parenthesis {
	//��
	Vec2 left;
	//�E
	Vec2 right;
};

// �������̍��W
const std::vector<Parenthesis>par = {
	{{0, 0}, {640 / 4, 480}},
	{{640 - 640 / 4, 0}, {640, 480}},
	{{0, 0}, {120, 60}}
};
