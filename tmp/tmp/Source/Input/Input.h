#pragma once
class Input
{
public:
	// デストラクタ
	~Input();

	// インスタンス変数の取得
	static Input& Get(void) {
		static Input instance;
		return instance;
	}

	// 処理
	void UpData(void);

	// キートリガーのチェック
	bool CheckTrigger(int key) const {
		return (state & key) && !(old_state & key);
	}
	// 現在のキー押下状態のチェック
	bool CheckPress(int key) const {
		return (state & key);
	}

private:
	// コンストラクタ
	Input();
	Input(const Input&) {
	}
	void operator=(const Input&) {
	}


	// 現在のキー状態
	int state;

	// 前のキー状態
	int old_state;
};

