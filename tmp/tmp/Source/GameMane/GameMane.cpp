#include "GameMane.h"
#include "../Charactor/Obj.h"
#include "../Charactor/CharData.h"

// �ő�z�u��
#define ARRANGEMENT_MAX 3

// �v���C���[�̔z�u�ʒu
const Vec2 arrangeMent_pl[] = {
	{ 0, 30 },
	{ 0, 170}, 
	{ 0, 320},
};

// �G�̔z�u�ʒu
const Vec2 arrangeMent_en[] = {
	{ 510, 30 },
	{ 510, 170 },
	{ 510, 320 },
};

// �R���X�g���N�^
GameMane::GameMane()
{
	id.clear();
	plID.resize(ARRANGEMENT_MAX);
	enID.resize(ARRANGEMENT_MAX);
	pl.clear();
	enemy.clear();

	for (auto itr = charData.begin(); itr != charData.end(); ++itr)
	{
		id.push_back(itr->first);
	}
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
		CharData tmp = charData[id];
		pl.push_back(std::make_shared<Obj>(id, tmp.hp, tmp.attack, tmp.def, tmp.speed, pos, reverse));
	}
}

// �G�L�����̐���
void GameMane::CreateEnemy(const std::string & id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2 & pos, const bool & reverse)
{
	if (charData.find(id) != charData.end())
	{
		CharData tmp = charData[id];
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
