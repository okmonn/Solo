#pragma once
#include <string>
#include <map>

// �L�����f�[�^
struct CharData {
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
std::map<std::string, CharData> charData {
	{ "1001010303", { 100, 10, 10, 1.0f } },
	{ "1007010303", { 100, 10, 10, 1.0f } },
	{ "1008010303", { 100, 10, 10, 1.0f } },
	{ "1011010303", { 100, 10, 10, 1.0f } },
	{ "1054010303", { 100, 10, 10, 1.0f } },
	{ "1055010303", { 100, 10, 10, 1.0f } },
};
