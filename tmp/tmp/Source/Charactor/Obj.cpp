#include "Obj.h"
#include "../ImageMane/ImageMane.h"
#include "DxLib.h"

// �A�j���[�V�����ڍs�t���[��
#define FLAM_MAX 10

// �ҋ@���Ԃ̉��Z�l
#define MOVE_CNT 0.5f

// �����ő吔X
#define RECT_X 9
// �����ő吔Y
#define RECT_Y 6

// �����T�C�Y
#define RECT_SIZE 64

// �A�j���[�V������
#define ANIM_MAX 3

// �̗͂̍ő吔
#define HP_MAX 100

// �R���X�g���N�^
Obj::Obj(const std::string& id, const int& hp, const int& attack, const int& def, const float& speed, const Vec2& pos, const bool& reverse) : mane(ImageMane::Get()),
	id(id + ".png"), image(mane.LoadImg("Material/img/" + this->id)), circle(mane.LoadImg("Material/img/Timer.png")), attackFlag(false), tmpDef(0),
	pos(pos), size(RECT_SIZE), index(0), flam(0), large(2), state(State::go), next(State::attack1), reverse(reverse), move(0.0f), target(0), die(false)
{
	anim.clear();

	this->hp = hp;
	this->attack = attack;
	this->def = def;
	this->speed = speed;

	func = &Obj::Go;

	SetAnim();
}

// �f�X�g���N�^
Obj::~Obj()
{
}

// �X�e�[�^�X�̃Z�b�g
void Obj::SetState(const State & state)
{
	if (this->state == state)
	{
		return;
	}

	this->state = state;
	index = 0;
	flam  = 0;

	switch (state)
	{
	case State::go:
		next = State::attack1;
		func = &Obj::Go;
		break;
	case State::attack1:
		func = &Obj::Attack1;
		break;
	case State::masicSet:
		func = &Obj::MasicSet;
		break;
	case State::gurd:
		func = &Obj::Gurd;
		break;
	case State::item:
		func = &Obj::Item;
		break;
	case State::win:
		func = &Obj::Win;
	case State::damage:
		func = &Obj::Damage;
		break;
	case State::die:
		func = &Obj::Die;
		break;
	default:
		break;
	}
}

// �`��
void Obj::Draw(void)
{
	if (state != State::win)
	{
		DrawCircleGauge(pos.x + size.x * large / 2, pos.y + size.y * large / 2, move, circle);
	}

	if (hp > 0)
	{
		DrawBox(pos.x, pos.y - 20, pos.x + size.x * large, pos.y - 10, GetColor(255, 255, 255), true);
		DrawBox(pos.x + 2, pos.y - 18, pos.x - 2 + size.x * large * hp / HP_MAX, pos.y - 12, GetColor(0, 0, 255), true);
	}

	if (reverse == false)
	{
		DrawRectModiGraph(pos.x, pos.y,
			pos.x + size.x * large, pos.y,
			pos.x + size.x * large, pos.y + size.y * large,
			pos.x, pos.y + size.y * large,
			size.x * (anim[state][index] % RECT_X), size.y * (anim[state][index] / RECT_X), size.x, size.y, image, true);
	}
	else
	{
		DrawRectModiGraph(pos.x + size.x * large, pos.y,
			pos.x, pos.y,
			pos.x, pos.y + size.y * large,
			pos.x + size.x * large, pos.y + size.y * large,
			size.x * (anim[state][index] % RECT_X), size.y * (anim[state][index] / RECT_X), size.x, size.y, image, true);
	}
}

// �A�j���[�V�����̃Z�b�g
void Obj::SetAnim(void)
{
	for (int s = 0; s < STATE_MAX; ++s)
	{
		anim[static_cast<State>(s)].resize(ANIM_MAX);
		for (unsigned int i = 0; i < anim[static_cast<State>(s)].size(); ++i)
		{
			anim[static_cast<State>(s)][i] = s * ANIM_MAX + i;
		}
	}
}

// �A�j���[�V�������I��邩�̃`�F�b�N
bool Obj::AnimEnd(void)
{
	if (index + 1 >= anim[state].size() && flam + 1 >= FLAM_MAX)
	{
		return true;
	}

	return false;
}

// �A�j���[�V�����Ǘ�
void Obj::Animetor(void)
{
	++flam;
	if (flam >= FLAM_MAX)
	{
		index = (anim[state].size() > index + 1) ? ++index : 0;
		flam = 0;
	}
}

// �ҋ@���̏���
void Obj::Go(void)
{
	if (state != State::go)
	{
		return;
	}

	move += MOVE_CNT * speed;
	if (move >= 100.0f)
	{
		move = 0.0f;
		SetState(next);
	}
}

// �U�����̏���
void Obj::Attack1(void)
{
	if (state != State::attack1)
	{
		return;
	}

	if (AnimEnd() == true)
	{
		SetState(State::go);
	}
	else
	{
		if (index == anim[state].size() / 2)
		{
			attackFlag = true;
		}
	}
}

// �r���ҋ@�̏���
void Obj::MasicSet(void)
{
	if (state != State::masicSet)
	{
		return;
	}

	if (AnimEnd() == true)
	{
		SetState(State::go);
	}
}

// �������̏���
void Obj::Win(void)
{
	if (state != State::win)
	{
		return;
	}
}

// �h�䎞�̏���
void Obj::Gurd(void)
{
	if (state != State::gurd)
	{
		return;
	}

	if (tmpDef <= 0)
	{
		tmpDef = def;
	}

	if (AnimEnd() == true)
	{
		SetState(State::go);
	}
}

// �A�C�e�����̏���
void Obj::Item(void)
{
	if (state != State::item)
	{
		return;
	}

	if (AnimEnd() == true)
	{
		SetState(State::go);
	}
}

// �_���[�W���̏���
void Obj::Damage(void)
{
	if (state != State::damage)
	{
		return;
	}

	if (hp <= 0)
	{
		SetState(State::die);
	}
	else
	{
		tmpDef = 0;
		if (AnimEnd() == true)
		{
			SetState(State::go);
		}
	}
}

// ���S���̏���
void Obj::Die(void)
{
	if (state != State::die)
	{
		return;
	}

	if (AnimEnd() == true)
	{
		die = true;
	}
}

// ����
void Obj::UpData(void)
{
	Animetor();

	(this->*func)();
}
