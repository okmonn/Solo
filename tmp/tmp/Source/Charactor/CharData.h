#pragma once
#include <string>
#include <map>

// �L�����f�[�^
struct Data {
	//�̗�
	int hp;
	//�U��
	int attack;
	//�h��
	int def;
	//���΂₳
	float speed;
};

// �L�����ꗗ
std::map<std::string, Data> charData {
	{ "1054010303", { 100, 10, 10, 0.1f } },
	{ "1055010303", { 100, 10, 10, 0.5f } },
};
