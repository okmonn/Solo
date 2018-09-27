#pragma once
#include "../etc/Vector2.h"
#include "../etc/Typedef.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>

class ImageMane;

class Obj
{
	// �_���[�W
	struct Dmg {
		//�_���[�W�l
		std::ostringstream num;
		//���W
		Vec2 pos;
	};

public:
	// �R���X�g���N�^
	Obj(const std::string& id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2& pos, const bool& reverse);
	// �f�X�g���N�^
	~Obj();

	// �X�e�[�^�X�̃Z�b�g
	void SetState(const State& state);

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

	// ID�̎擾
	std::string GetID(void) {
		std::string id = this->id.substr(0, this->id.find_last_of('.'));
		return id;
	}

	// ���W�̎擾
	Vec2 GetPos(void) const {
		return pos;
	}
	// ���W�̃Z�b�g
	void SetPos(const Vec2& pos) {
		this->pos = pos;
	}

	// �T�C�Y�̎擾
	Vec2 GetSize(void) const {
		return size * large;
	}
	// �T�C�Y�̃Z�b�g
	void SetSize(const Vec2& size) {
		this->size = size;
	}

	// �g�嗦�̎擾
	int GetLarge(void) const {
		return large;
	}
	// �g�嗦�̃Z�b�g
	void SetLarge(const int& large) {
		this->large = large;
	}

	// �X�e�[�^�X�̎擾
	State GetState(void) const {
		return state;
	}

	// ���̃X�e�[�^�X�̎擾
	State GetNextState(void) const {
		return next;
	}
	// ���̃X�e�[�^�X�̃Z�b�g
	void SetnextState(const State& state) {
		next = state;
	}

	// �ҋ@���Ԃ̎擾
	float GetMove(void) const {
		return move;
	}
	// �ҋ@���Ԃ̃Z�b�g
	void SetMove(const float& i) {
		this->move = i;
	}

	// �^�[�Q�b�g�̎擾
	int GetTarget(void) const {
		return target;
	}
	// �^�[�Q�b�g�̃Z�b�g
	void SetTarget(const int& target) {
		this->target = target;
	}

	// ���S�t���O�̎擾
	bool GetDie(void) const {
		return die;
	}

	// �U���t���O�̎擾
	bool GetAttackFlag(void) const {
		return attackFlag;
	}
	// �U���t���O�̃Z�b�g
	void SetAttackFlag(const bool& flag) {
		this->attackFlag = flag;
	}

	// �̗͂̎擾
	int Gethp(void) const {
		return hp;
	}
	// �̗͂̃Z�b�g
	void SetHp(const int& hp) {
		this->hp = hp;
	}
	// �̗͂̌���
	void Decrease(const int& i) {
		if (tmpDef - i < 0)
		{
			old_hp = this->hp;
			this->hp += tmpDef - i;
		}
	}

	// �U���l�̎擾
	int GetAttack(void) const {
		return attack;
	}
	// �U���l�̃Z�b�g
	void SetAttack(const int& attack) {
		this->attack = attack;
	}

	// �h��l�̎擾
	int GetDef(void) const {
		return def;
	}
	// �h��l�̃Z�b�g
	void SetDef(const int& def) {
		this->def = def;
	}

	// �f�����̎擾
	float GetSpeed(void) const {
		return speed;
	}
	// �f�����̃Z�b�g
	void SetSpeed(const float& speed) {
		this->speed = speed;
	}

private:
	// �A�j���[�V�����̃Z�b�g
	void SetAnim(void);

	// �A�j���[�V�������I��邩�̃`�F�b�N
	bool AnimEnd(void);

	// �A�j���[�V�����Ǘ�
	void  Animetor(void);

	// �ҋ@���̏���
	void Go(void);

	// �U�����̏���
	void Attack1(void);

	// �r���ҋ@�̏���
	void MasicSet(void);

	// �������̏���
	void Win(void);

	// �h�䎞�̏���
	void Gurd(void);

	// �A�C�e�����̏���
	void Item(void);

	// �_���[�W���̏���
	void Damage(void);

	// ���S���̏���
	void Die(void);


	// �C���[�W�}�l
	ImageMane& mane;

	// ID
	std::string id;

	// �摜�f�[�^
	int image;

	// ���W
	Vec2 pos; 

	// �T�C�Y
	Vec2 size;

	// �A�j���[�V�����C���f�b�N�X
	unsigned int index;

	// �A�j���[�V�����t���[��
	int flam;

	// �g�嗦
	int large;

	// �X�e�[�^�X
	State state;

	// ���̃X�e�[�^�X
	State next;

	// ���]�t���O
	bool reverse;

	// �A�j���[�V�����f�[�^
	std::map<State, std::vector<int>>anim;

	// �s���J�n�܂ł̑ҋ@����
	float move;

	// �^�[�Q�b�g�C���f�b�N�X
	int target;

	// ���S�t���O
	bool die;

	// �T�[�N���摜
	int circle;

	// �U���t���O
	bool attackFlag;

	// �̗�
	int hp;

	// �U���l
	int attack;

	// �h��l
	int def;

	// �f����
	float speed;

	// ���݂̖h��l
	int tmpDef;

	// �O�̗̑͒l
	int old_hp;

	// �_���[�W�t���[��
	int damageFlam;

	// �_���[�W
	Dmg damage;

	// �֐��|�C���^
	void (Obj::*func)(void);
};

