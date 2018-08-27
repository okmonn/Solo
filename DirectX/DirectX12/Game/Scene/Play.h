#pragma once
#include "Scene.h"

class Play :
	public Scene
{
public:
	// コンストラクタ
	Play();
	// デストラクタ
	~Play();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:

};

