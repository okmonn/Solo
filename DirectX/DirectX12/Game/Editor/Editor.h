#pragma once
#include "../etc/Share.h"
#include <vector>
#include <string>
#include <string>

class Editor
{
public:
	// コンストラクタ
	Editor();
	// デストラクタ
	~Editor();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

	// セーブ
	bool Save(void);

	// 読み込み
	bool Load(void);

private:
	// ノーツのセット
	void SetNote(LaneType type, unsigned int key1, unsigned int key2, unsigned int key3);

	// 文字入力
	void Scan(std::string m);

	// 経過フレーム
	int flam;

	// 押下時間
	Notes note[LaneType::TYPE_MAX];

	// 譜面データ
	std::vector<Notes>data;
};

