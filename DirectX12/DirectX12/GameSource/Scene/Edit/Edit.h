#pragma once
#include "../Scene.h"

class Edit :
	public Scene
{
public:
	// コンストラクタ
	Edit();
	// デストラクタ
	~Edit();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:

};

