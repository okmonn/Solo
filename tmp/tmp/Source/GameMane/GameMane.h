#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <vector>
#include <list>
#include <memory>

class Obj;

class GameMane
{
public:
	// �f�X�g���N�^
	~GameMane();

	// �C���X�^���X�ϐ��̎擾
	static GameMane& Get(void) {
		static GameMane instance;
		return instance;
	}

	// ID�̃Z�b�g
	void SetID_PL(int index, const std::string& id);
	// ID�̃Z�b�g
	void SetID_EN(int index, const std::string& id);

	// �`��
	void Draw(void);

	// ����
	void UpData(void);
	
	// �N���A
	void Clear(void);

	// �v���C���[�L�����̎擾
	std::list<std::shared_ptr<Obj>> GetPL(void) {
		return pl;
	}
	// �v���C���[�L�����̎擾
	std::shared_ptr<Obj> GetPL(int index);

	//	�G�L�����̎擾
	std::list<std::shared_ptr<Obj>> GetEn(void) {
		return enemy;
	}
	// �G�L�����̎擾
	std::shared_ptr<Obj> GetEn(int index);

private:
	// �R���X�g���N�^
	GameMane();
	GameMane(const GameMane&) {
	}
	void operator=(const GameMane&) {
	}


	// �v���C���[�L�����̐���
	void CreatePl(const std::string& id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2& pos = 0, const bool& reverse = true);
	// �G�L�����̐���
	void CreateEnemy(const std::string& id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2& pos = 0, const bool& reverse = false);

	// �L�����̐���
	void CreateObj(void);

	// �`��
	void Draw(const std::list<std::shared_ptr<Obj>>& list);

	// ����
	void UpData(std::list<std::shared_ptr<Obj>>& list);


	// �L����ID
	std::vector<std::string>plID;

	// �GID
	std::vector<std::string>enID;

	// �v���C���[�L����
	std::list<std::shared_ptr<Obj>>pl;

	// �G�L����
	std::list<std::shared_ptr<Obj>>enemy;
};

