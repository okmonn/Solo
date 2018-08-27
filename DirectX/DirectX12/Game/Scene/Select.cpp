#include "Select.h"
#include "../Game.h"
#include "../../Func.h"
#include <algorithm>
using namespace func;

// コンストラクタ
Select::Select()
{
	fileName.clear();
	func = (GetMidiDevNum() == 0) ? &Select::Key : &Select::Midi;

	LoadDir(".");
}

// デストラクタ
Select::~Select()
{
}

// 描画
void Select::Draw(void)
{
}

// 配列に追加
void Select::AddFileName(const fs::path& path)
{
	//ファイルの場合
	if (fs::is_regular_file(path))
	{
		std::cout << "file：" << path.filename() << "\n" << std::endl;
		fileName.push_back(path.filename().string());
	}
	else if (fs::is_directory(path))
	{
		std::cout << "dir.：" << path.string() << "\n" << std::endl;
	}
}

// ディレクトリの読み込み
void Select::LoadDir(const std::string& path)
{
	//列挙の起点
	fs::path p(path.c_str());

	for (auto& i : fs::recursive_directory_iterator(p))
	{
		AddFileName(i);
	}
}

// キー入力
void Select::Key(void)
{
}

// MIDI入力
void Select::Midi(void)
{
}

// 処理
void Select::UpData(void)
{
	(this->*func)();
}

