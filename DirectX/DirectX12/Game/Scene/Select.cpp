#include "Select.h"
#include "../Game.h"
#include "../../Func.h"
#include <algorithm>
using namespace func;

// �R���X�g���N�^
Select::Select()
{
	fileName.clear();
	func = (GetMidiDevNum() == 0) ? &Select::Key : &Select::Midi;

	LoadDir(".");
}

// �f�X�g���N�^
Select::~Select()
{
}

// �`��
void Select::Draw(void)
{
}

// �z��ɒǉ�
void Select::AddFileName(const fs::path& path)
{
	//�t�@�C���̏ꍇ
	if (fs::is_regular_file(path))
	{
		std::cout << "file�F" << path.filename() << "\n" << std::endl;
		fileName.push_back(path.filename().string());
	}
	else if (fs::is_directory(path))
	{
		std::cout << "dir.�F" << path.string() << "\n" << std::endl;
	}
}

// �f�B���N�g���̓ǂݍ���
void Select::LoadDir(const std::string& path)
{
	//�񋓂̋N�_
	fs::path p(path.c_str());

	for (auto& i : fs::recursive_directory_iterator(p))
	{
		AddFileName(i);
	}
}

// �L�[����
void Select::Key(void)
{
}

// MIDI����
void Select::Midi(void)
{
}

// ����
void Select::UpData(void)
{
	(this->*func)();
}

