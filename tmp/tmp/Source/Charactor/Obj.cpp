#include "Obj.h"
#include "../ImageMane/ImageMane.h"
#include "DxLib.h"

// アニメーション移行フレーム
#define FLAM_MAX 10

// 待機時間の加算値
#define MOVE_CNT 0.5f

// 分割最大数X
#define RECT_X 9
// 分割最大数Y
#define RECT_Y 6

// 分割サイズ
#define RECT_SIZE 64

// アニメーション数
#define ANIM_MAX 3

// コンストラクタ
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

// デストラクタ
Obj::~Obj()
{
}

// ステータスのセット
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

// 描画
void Obj::Draw(void)
{
	if (state != State::win)
	{
		DrawCircleGauge(pos.x + size.x * large / 2, pos.y + size.y * large / 2, move, circle);
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

// アニメーションのセット
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

// アニメーションが終わるかのチェック
bool Obj::AnimEnd(void)
{
	if (index + 1 >= anim[state].size() && flam + 1 >= FLAM_MAX)
	{
		return true;
	}

	return false;
}

// アニメーション管理
void Obj::Animetor(void)
{
	++flam;
	if (flam >= FLAM_MAX)
	{
		index = (anim[state].size() > index + 1) ? ++index : 0;
		flam = 0;
	}
}

// 待機時の処理
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

// 攻撃時の処理
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

// 攻撃時の処理
void Obj::Attack2(void)
{
	if (state != State::attack2)
	{
		return;
	}

	if (AnimEnd() == true)
	{
		SetState(State::go);
	}
}

// 詠唱待機の処理
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

// 勝利時の処理
void Obj::Win(void)
{
	if (state != State::win)
	{
		return;
	}
}

// 防御時の処理
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

// アイテム時の処理
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

// ダメージ時の処理
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

// 死亡時の処理
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

// 処理
void Obj::UpData(void)
{
	Animetor();

	(this->*func)();
}
