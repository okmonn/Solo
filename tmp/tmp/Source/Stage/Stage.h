#pragma once
#include <string>
#include <vector>

class Stage
{
public:
	// デストラクタ
	~Stage();

	// インスタンス変数の取得
	static Stage& Get(void) {
		static Stage instance;
		return instance;
	}

	// 読み込み
	void LoadStage(void);

	// IDのクリア
	void Clear(void);

	// ステージインデックスの取得
	int GetIndex(void) const {
		return index;
	}
	// ステージインデックスのセット
	void SetIndex(const int& index) {
		this->index = index;
	}

	// 敵のID取得
	std::vector<std::string> GetID(void) const {
		return id;
	}
	std::string GetID(const unsigned int& i) const {
		return id[i];
	}

private:
	// コンストラクタ
	Stage();
	Stage(const Stage&) {
	}
	void operator=(const Stage&) {
	}


	// ステージインデックス
	int index;

	// ステージの敵ID
	std::vector<std::string>id;
};

