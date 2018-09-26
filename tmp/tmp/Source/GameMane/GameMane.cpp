#include "GameMane.h"
#include "../Obj/Obj.h"
#include "../Obj/CharData.h"

// �ő�z�u��
#define ARRANGEMENT_MAX 3

// �v���C���[�̔z�u�ʒu
const Vec2 arrangeMent_pl[] = {
	{ 0, 0 },
	{ 0, 150}, 
	{ 0, 300},
};

// �G�̔z�u�ʒu
const Vec2 arrangeMent_en[] = {
	{ 510, 0 },
	{ 510, 150 },
	{ 510, 300 },
};

// �R���X�g���N�^
GameMane::GameMane()
{
	plID.resize(ARRANGEMENT_MAX);
	enID.resize(ARRANGEMENT_MAX);
	pl.clear();
	enemy.clear();

	SetID_PL(0, "1054010303");
	SetID_PL(1, "1055010303");
	SetID_PL(2, "1055010303");

	SetID_EN(0, "1054010303");
	SetID_EN(1, "1055010303");
	SetID_EN(2, "1055010303");

	CreateObj();
}

// �f�X�g���N�^
GameMane::~GameMane()
{
}

// �v���C���[�L�����̎擾
std::shared_ptr<Obj> GameMane::GetPL(int index)
{
	int n = 0;
	for (auto itr = pl.begin(); itr != pl.end(); ++itr)
	{
		++n;
		if (n > index)
		{
			return (*itr);
		}
	}

	return std::shared_ptr<Obj>();
}

// �G�L�����̎擾
std::shared_ptr<Obj> GameMane::GetEn(int index)
{
	int n = 0;
	for (auto itr = enemy.begin(); itr != enemy.end(); ++itr)
	{
		++n;
		if (n > index)
		{
			return (*itr);
		}
	}

	return std::shared_ptr<Obj>();
}

// �v���C���[�L�����̐���
void GameMane::CreatePl(const std::string & id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2 & pos, const bool & reverse)
{
	if (charData.find(id) != charData.end())
	{
		Data tmp = charData[id];
		pl.push_back(std::make_shared<Obj>(id, tmp.hp, tmp.attack, tmp.def, tmp.speed, pos, reverse));
	}
}

// �G�L�����̐���
void GameMane::CreateEnemy(const std::string & id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2 & pos, const bool & reverse)
{
	if (charData.find(id) != charData.end())
	{
		Data tmp = charData[id];
		enemy.push_back(std::make_shared<Obj>(id, tmp.hp, tmp.attack, tmp.def, tmp.speed, pos, reverse));
	}
}

// �L�����̐���
void GameMane::CreateObj(void)
{
	for (int i = 0; i < 3; ++i)
	{
		//�v���C���[�L����
		CreatePl(plID[i], 1, 1, 0, 1.0f, arrangeMent_pl[i]);
		CreateEnemy(enID[i], 1, 1, 0, 1.0f, arrangeMent_en[i]);
	}
}

// �`��
void GameMane::Draw(const std::list<std::shared_ptr<Obj>>& list)
{
	for (auto itr = list.begin(); itr != list.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

// ID�̃Z�b�g
void GameMane::SetID_PL(int index, const std::string & id)
{
	if (index >= ARRANGEMENT_MAX)
	{
		return;
	}

	this->plID[index] = id;
}

// ID�̃Z�b�g
void GameMane::SetID_EN(int index, const std::string & id)
{
	if (index >= ARRANGEMENT_MAX)
	{
		return;
	}

	this->enID[index] = id;
}

// �`��
void GameMane::Draw(void)
{
	Draw(pl);
	Draw(enemy);
}

// ����
void GameMane::UpData(std::list<std::shared_ptr<Obj>>& list)
{
	for (auto itr = list.begin(); itr != list.end();)
	{
		(*itr)->UpData();

		if ((*itr)->GetDie() == true)
		{
			itr = list.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

// ����
void GameMane::UpData(void)
{
	UpData(pl);
	UpData(enemy);
}

// �N���A
void GameMane::Clear(void)
{
	pl.clear();
	enemy.clear();
}
