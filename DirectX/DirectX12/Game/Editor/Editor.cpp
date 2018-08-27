#include "Editor.h"
#include "Character.h"
#include "../../Func.h"
using namespace func;

// �t�@�C���l�[���ő啶����
#define MAX 20

// �R���X�g���N�^
Editor::Editor() : 
	flam(0)
{
	memset(note, 0, sizeof(note));
	data.clear();
}

// �f�X�g���N�^
Editor::~Editor()
{
}

// �`��
void Editor::Draw(void)
{
}

// �m�[�c�̃Z�b�g
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

			//�ǉ�
			data.push_back(note[type]);

			//���Z�b�g
			note[type] = {};
		}
	}
}

// ��������
void Editor::Scan(std::string m)
{
	while (!TriggerKey(INPUT_RETURN))
	{
		for (int i = 0; i < 256; ++i)
		{
			if (TriggerKey(i))
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

// ����
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

// �Z�[�u
bool Editor::Save(void)
{
	std::string fileName;

	Scan(fileName);
	
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "wb") != 0)
	{
		return false;
	}

	//�f�[�^��
	unsigned int size = data.size();
	fwrite(&size, sizeof(size), 1, file);

	for (auto& i : data)
	{
		fwrite(&i, sizeof(Notes), 1, file);
	}

	fclose(file);

	return true;
}

// �ǂݍ���
bool Editor::Load(void)
{
	std::string fileName;

	Scan(fileName);

	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		return false;
	}

	//�f�[�^��
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
