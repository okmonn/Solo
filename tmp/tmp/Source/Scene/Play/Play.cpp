#include "Play.h"
#include "../Result/Result.h"
#include "../../Obj/Obj.h"
#include "../../Game/Game.h"
#include "../../GameMane/GameMane.h"
#include "../../Mouse/Mouse.h"
#include "DxLib.h"

// �^�[�Q�b�g�摜�̃I�t�Z�b�g
#define TARGET_OFFSET 15

// �R�}���h�ő吔
#define COMMAND_MAX 4

const std::string comName[] = {
	"��������",
	"�ڂ�����",
	"���܂���",
	"�����ӂ�"
};

// �R���X�g���N�^
Play::Play() : mane(GameMane::Get()), mouse(Mouse::Get()),
	select(0), target(0)
{
	com.resize(COMMAND_MAX);

	draw = &Play::BattleDraw;
	updata = &Play::BattleUpData;

	ComInit();
	Load("Material/img/Target.png", "target", { 150, 150 }, { mane.GetEn(target)->GetPos().x - TARGET_OFFSET, mane.GetEn(target)->GetPos().y });
}

// �f�X�g���N�^
Play::~Play()
{
}

// �R�}���h�̃Z�b�g
void Play::SetCom(int index, const std::string name, const Vec2 & pos, const Vec2 & size)
{
	com[index].name   = name;
	com[index].pos    = pos;
	com[index].size   = size;
	com[index].color  = GetColor(255, 255, 255);
	com[index].offset = { 20, 10 };
}

// �R�}���h�̏�����
void Play::ComInit(void)
{
	for (int i = 0; i < COMMAND_MAX; ++i)
	{
		SetCom(i, comName[i], { 200 + 150 * (i % (COMMAND_MAX / 2)), 200 + 100 * (i / (COMMAND_MAX / 2)) }, { 100, 50 });
	}
}

// �퓬�`��
void Play::BattleDraw(void)
{
	for (unsigned int i = 0; i < com.size(); ++i)
	{
		DrawBox(com[i].pos.x - com[i].offset.x / 2, com[i].pos.y - com[i].offset.y / 2,
			com[i].pos.x + com[i].size.x + com[i].offset.x / 2, com[i].pos.y + com[i].size.y + com[i].offset.y / 2, GetColor(0, 255, 0), false);
		DrawString(com[i].pos.x, com[i].pos.y, com[i].name.c_str(), com[i].color);
	}

	mane.Draw();

	//�I���L����
	if (mane.GetPL().size() != 0)
	{
		DrawBox(mane.GetPL(select)->GetPos().x, mane.GetPL(select)->GetPos().y,
			mane.GetPL(select)->GetPos().x + mane.GetPL(select)->GetSize().x, mane.GetPL(select)->GetPos().y + mane.GetPL(select)->GetSize().y,
			GetColor(0, 255, 0), false);
	}

	//�^�[�Q�b�g�L����
	if (mane.GetEn().size() != 0)
	{
		Scene::DrawGraph("target");
	}
}

// �I���`��
void Play::EndDraw(void)
{
	mane.Draw();
}

// �퓬����
void Play::BattleUpData(void)
{
	if (mane.GetEn().size() == 0 || mane.GetPL().size() == 0)
	{
		draw = &Play::EndDraw;
		updata = &Play::EndUpData;
	}
	else
	{
		for (unsigned int i = 0; i < com.size(); ++i)
		{
			if ((com[i].pos.x - com[i].offset.x / 2 < mouse.GetPos().x && mouse.GetPos().x < com[i].pos.x + com[i].size.x + com[i].offset.x / 2)
				&& (com[i].pos.y - com[i].offset.y / 2 < mouse.GetPos().y && mouse.GetPos().y < com[i].pos.y + com[i].size.y + com[i].offset.y / 2))
			{
				if (mouse.TrigerClick() == true && mane.GetPL(select)->GetState() == State::go)
				{
					switch (i)
					{
					case 0:
						mane.GetPL(select)->SetnextState(State::attack1);
						break;
					case 1:
						mane.GetPL(select)->SetnextState(State::gurd);
						break;
					case 2:
						mane.GetPL(select)->SetnextState(State::masicSet);
						break;
					case 3:
						mane.GetPL(select)->SetnextState(State::item);
						break;
					default:
						break;
					}

				}
			}
			else
			{
				com[i].color = GetColor(255, 255, 255);
			}
		}

		//�^�[�Q�b�g�̃Z�b�g
		for (unsigned int i = 0; i < mane.GetEn().size(); ++i)
		{
			if (mane.GetEn(i)->GetPos().x < mouse.GetPos().x && mouse.GetPos().x < mane.GetEn(i)->GetPos().x + mane.GetEn(i)->GetSize().x
				&& mane.GetEn(i)->GetPos().y < mouse.GetPos().y && mouse.GetPos().y < mane.GetEn(i)->GetPos().y + mane.GetEn(i)->GetSize().y)
			{
				if (mouse.TrigerClick() == true && mane.GetEn(target)->GetState() != State::die)
				{
					target = i;
					for (unsigned int pl = 0; pl < mane.GetPL().size(); ++pl)
					{
						mane.GetPL(pl)->SetTarget(target);
					}
				}
			}
		}

		//�I���L�����̃Z�b�g
		for (unsigned int i = 0; i < mane.GetPL().size(); ++i)
		{
			if (mane.GetPL(i)->GetPos().x < mouse.GetPos().x && mouse.GetPos().x < mane.GetPL(i)->GetPos().x + mane.GetPL(i)->GetSize().x
				&& mane.GetPL(i)->GetPos().y < mouse.GetPos().y && mouse.GetPos().y < mane.GetPL(i)->GetPos().y + mane.GetPL(i)->GetSize().y)
			{
				if (mouse.TrigerClick() == true && mane.GetPL(i)->GetState() != State::die)
				{
					select = i;
				}
			}
		}

		int index = 0;
		switch (mane.GetPL(select)->GetNextState())
		{
		case State::attack1:
			index = 0;
			break;
		case State::gurd:
			index = 1;
			break;
		case State::masicSet:
			index = 2;
			break;
		case State::item:
			index = 3;
			break;
		default:
			break;
		}

		com[index].color = GetColor(255, 0, 0);

		mane.UpData();

		//�v���C���[�L�����̍U��
		for (unsigned int i = 0; i < mane.GetPL().size(); ++i)
		{
			if (mane.GetPL(i)->GetAttackFlag() == true)
			{
				mane.GetEn(target)->Decrease(mane.GetPL(i)->GetAttack());
				mane.GetEn(target)->SetState(State::damage);
				mane.GetPL(i)->SetAttackFlag(false);
			}
		}

		//�G�L�����̍U��
		for (unsigned int i = 0; i < mane.GetEn().size(); ++i)
		{
			if (mane.GetEn(i)->GetAttackFlag() == true)
			{
				mane.GetPL(0)->Decrease(mane.GetEn(i)->GetAttack());
				mane.GetPL(0)->SetState(State::damage);
				mane.GetEn(i)->SetAttackFlag(false);
			}
		}

		//�I���L�����̍X�V
		if (mane.GetPL().size() != 0)
		{
			if (select >= (int)mane.GetPL().size())
			{
				select = mane.GetPL().size() - 1;
			}
		}

		//�^�[�Q�b�g�摜�̈ʒu�X�V
		if (mane.GetEn().size() != 0)
		{
			if (mane.GetEn(target)->GetState() == State::die)
			{
				target = 0;
			}

			image["target"].pos = { mane.GetEn(target)->GetPos().x - 15, mane.GetEn(target)->GetPos().y };
		}
	}
}

// �I������
void Play::EndUpData(void)
{
	if (mane.GetPL().size() != 0)
	{
		for (unsigned int i = 0; i < mane.GetPL().size(); ++i)
		{
			mane.GetPL(i)->SetMove(0.0f);
		}
	}
	else
	{
		for (unsigned int i = 0; i < mane.GetEn().size(); ++i)
		{
			mane.GetEn(i)->SetMove(0.0f);
		}
	}
}

// �`��
void Play::Draw(void)
{
	(this->*draw)();
}

// ����
void Play::UpData(void)
{
	(this->*updata)();
}
