#pragma once
#include "../Scene.h"

class Result :
	public Scene
{
public:
	// コンストラクタ
	Result();
	// デストラクタ
	~Result();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:

};

