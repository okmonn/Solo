#include "Editor.h"
#include "Character.h"
#include "../../Func.h"
using namespace func;

// コンストラクタ
Editor::Editor() : 
	flam(0)
{
	memset(note, 0, sizeof(note));
	data.clear();
}

// デストラクタ
Editor::~Editor()
{
}

// 描画
void Editor::Draw(void)
{
}

// ノーツのセット
void Editor::SetNote(LaneType type, unsigned int key1, unsigned int key2, unsigned int key3)
{
	if (CheckKey(key1) || CheckKey(key2) || CheckKey(key3))
	{
		++note[type].time;
	}
	else
	{
		if (note[type].time > 0)
		{
			note[type].type = type;
			note[type].start = flam - note[type].time;

			//追加
			data.push_back(note[type]);

			//リセット
			note[type] = {};
		}
	}
}

// 文字入力
void Editor::Scan(std::string m)
{
	while (!TriggerKey(INPUT_RETURN))
	{
		for (int i = 0; i < 256; ++i)
		{
			if (TriggerKey(i))
			{
				if (i == 0x0e && m.size() > 0)
				{
					m.pop_back();
				}
				else
				{
					for (auto& itr : character)
					{
						if (itr.first != i)
						{
							continue;
						}
						else
						{
							m.push_back(itr.second);
							break;
						}
					}
				}
			}
		}
	}
}

// 処理
void Editor::UpData(void)
{
	SetNote(LaneType::TYPE_A, INPUT_A,         INPUT_S,     INPUT_D);
	SetNote(LaneType::TYPE_B, INPUT_F,         INPUT_G,     INPUT_H);
	SetNote(LaneType::TYPE_C, INPUT_J,         INPUT_K,     INPUT_L);
	SetNote(LaneType::TYPE_D, INPUT_SEMICOLON, INPUT_COLON, INPUT_RBRACKET);

	if (TriggerKey(INPUT_RSHIFT))
	{
		Save();
	}
	if (TriggerKey(INPUT_LSHIFT))
	{
		Load();
	}

	++flam;
}

// セーブ
bool Editor::Save(void)
{
	std::string fileName;

	Scan(fileName);
	
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "wb") != 0)
	{
		return false;
	}

	//データ数
	unsigned int size = data.size();
	fwrite(&size, sizeof(size), 1, file);

	for (auto& i : data)
	{
		fwrite(&i, sizeof(Notes), 1, file);
	}

	fclose(file);

	return true;
}

// 読み込み
bool Editor::Load(void)
{
	std::string fileName;

	Scan(fileName);

	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		return false;
	}

	//データ数
	unsigned int size = 0;
	fread(&size, sizeof(size), 1, file);

	data.resize(size);

	for (auto& i : data)
	{
		fread(&i, sizeof(Notes), 1, file);
	}

	fclose(file);

	return true;
}
