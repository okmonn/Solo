#pragma once
#include "../Scene.h"
#include <vector>
#include <string>

class Select :
	public Scene
{
public:
	// コンストラクタ
	Select();
	// デストラクタ
	~Select();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// キー入力
	void Key(void);

	// MIDI入力
	void Midi(void);


	// ディレクトリ内のファイル名
	std::vector<std::string>fileName;

	// 関数ポインタ
	void (Select::*func)(void);
};

