#include "Play.h"
#include "../Select/Select.h"
#include "../../Charactor/Obj.h"
#include "../../Game/Game.h"
#include "../../GameMane/GameMane.h"
#include "../../Stage/Stage.h"
#include "../../Mouse/Mouse.h"
#include "../../BackGround/BackGround.h"
#include "DxLib.h"

// ターゲット画像のオフセット
#define TARGET_OFFSET 15

// コマンド最大数
#define COMMAND_MAX 4

// 終了フレーム
#define END_FLAM 100

const std::string comName[] = {
	"こうげき",
	"ぼうぎょ",
	"かまえる",
	"かいふく"
};

// コンストラクタ
Play::Play() : mane(GameMane::Get()), mouse(Mouse::Get()), stage(Stage::Get()), back(std::make_shared<BackGround>()),
	select(0), target(0), flam(0)
{
	mane.Clear();
	com.resize(COMMAND_MAX);

	draw = &Play::BattleDraw;
	updata = &Play::BattleUpData;

	ComInit();
	LoadEnemy();
	mane.CreateObj();
	Load("Material/img/Target.png", "target", { 150, 150 }, { mane.GetEn(target)->GetPos().x - TARGET_OFFSET, mane.GetEn(target)->GetPos().y - TARGET_OFFSET });
}

// デストラクタ
Play::~Play()
{
}

// コマンドのセット
void Play::SetCom(int index, const std::string name, const Vec2 & pos, const Vec2 & size)
{
	com[index].name   = name;
	com[index].pos    = pos;
	com[index].size   = size;
	com[index].color  = GetColor(255, 255, 255);
	com[index].offset = { 20, 10 };
}

// コマンドの初期化
void Play::ComInit(void)
{
	for (int i = 0; i < COMMAND_MAX; ++i)
	{
		SetCom(i, comName[i], { 200 + 150 * (i % (COMMAND_MAX / 2)), 200 + 100 * (i / (COMMAND_MAX / 2)) }, { 100, 50 });
	}
}

// 敵の読み込み
void Play::LoadEnemy(void)
{
	for (unsigned int i = 0; i < stage.GetID().size(); ++i)
	{
		mane.SetID_EN(i, stage.GetID(i));
	}
}

// 戦闘描画
void Play::BattleDraw(void)
{
	for (unsigned int i = 0; i < com.size(); ++i)
	{
		DrawBox(com[i].pos.x - com[i].offset.x / 2, com[i].pos.y - com[i].offset.y / 2,
			com[i].pos.x + com[i].size.x + com[i].offset.x / 2, com[i].pos.y + com[i].size.y + com[i].offset.y / 2, GetColor(0, 255, 0), false);
		DrawString(com[i].pos.x, com[i].pos.y, com[i].name.c_str(), com[i].color);
	}

	mane.Draw();

	//選択キャラ
	if (mane.GetPL().size() != 0)
	{
		DrawBox(mane.GetPL(select)->GetPos().x, mane.GetPL(select)->GetPos().y,
			mane.GetPL(select)->GetPos().x + mane.GetPL(select)->GetSize().x, mane.GetPL(select)->GetPos().y + mane.GetPL(select)->GetSize().y,
			GetColor(0, 255, 0), false);
	}

	//ターゲットキャラ
	if (mane.GetEn().size() != 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		Scene::DrawGraph("target");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// 終了描画
void Play::EndDraw(void)
{
	mane.Draw();

	if (mane.GetPL().size() != 0)
	{

	}
	else
	{

	}
}

// 描画
void Play::Draw(void)
{
	back->Draw();

	(this->*draw)();
}

// 戦闘処理
void Play::BattleUpData(void)
{
	if (mane.GetEn().size() == 0 || mane.GetPL().size() == 0)
	{
		flam = 0;
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

					break;
				}
			}
			else
			{
				com[i].color = GetColor(255, 255, 255);
			}
		}

		//ターゲットのセット
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
					break;
				}
			}
		}

		//選択キャラのセット
		for (unsigned int i = 0; i < mane.GetPL().size(); ++i)
		{
			if (mane.GetPL(i)->GetPos().x < mouse.GetPos().x && mouse.GetPos().x < mane.GetPL(i)->GetPos().x + mane.GetPL(i)->GetSize().x
				&& mane.GetPL(i)->GetPos().y < mouse.GetPos().y && mouse.GetPos().y < mane.GetPL(i)->GetPos().y + mane.GetPL(i)->GetSize().y)
			{
				if (mouse.TrigerClick() == true && mane.GetPL(i)->GetState() != State::die)
				{
					select = i;
				}
				break;
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

		if (mane.GetEn().size() != 0)
		{
			//プレイヤーキャラの攻撃
			for (unsigned int i = 0; i < mane.GetPL().size(); ++i)
			{
				if (mane.GetPL(i)->GetAttackFlag() == true && mane.GetEn(target)->GetState() != State::damage)
				{
					mane.GetEn(target)->Decrease(mane.GetPL(i)->GetAttack());
					mane.GetEn(target)->SetState(State::damage);
					mane.GetPL(i)->SetAttackFlag(false);
				}
				else
				{
					mane.GetPL(i)->SetAttackFlag(false);
				}
			}
		}

		if (mane.GetPL().size() != 0)
		{
			//敵キャラの攻撃
			for (unsigned int i = 0; i < mane.GetEn().size(); ++i)
			{
				if (mane.GetEn(i)->GetAttackFlag() == true && mane.GetPL(0)->GetState() != State::damage)
				{
					mane.GetPL(0)->Decrease(mane.GetEn(i)->GetAttack());
					mane.GetPL(0)->SetState(State::damage);
					mane.GetEn(i)->SetAttackFlag(false);
				}
				else
				{
					mane.GetEn(i)->SetAttackFlag(false);
				}
			}
		}

		//選択キャラの更新
		if (mane.GetPL().size() != 0)
		{
			if (select >= (int)mane.GetPL().size())
			{
				select = mane.GetPL().size() - 1;
			}
		}

		//ターゲット画像の位置更新
		if (mane.GetEn().size() != 0)
		{
			if (mane.GetEn(target)->GetState() == State::die)
			{
				target = 0;
			}

			image["target"].pos = { mane.GetEn(target)->GetPos().x - TARGET_OFFSET, mane.GetEn(target)->GetPos().y - TARGET_OFFSET };
		}
	}
}

// 終了処理
void Play::EndUpData(void)
{
	++flam;
	if (flam >= END_FLAM)
	{
		game.ChangeScene(new Select());
	}
	else
	{
		if (mane.GetPL().size() != 0)
		{
			for (unsigned int i = 0; i < mane.GetPL().size(); ++i)
			{
				mane.GetPL(i)->SetMove(0.0f);
				if (mane.GetPL(i)->GetState() != State::win)
				{
					mane.GetPL(i)->SetState(State::win);
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < mane.GetEn().size(); ++i)
			{
				mane.GetEn(i)->SetMove(0.0f);
				if (mane.GetEn(i)->GetState() != State::win)
				{
					mane.GetEn(i)->SetState(State::win);
				}
			}
		}

		mane.UpData();
	}
}

// 処理
void Play::UpData(void)
{
	(this->*updata)();
}
