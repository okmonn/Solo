#pragma once
#include "../BasePlay.h"
#include <vector>
#include <memory>

class GameMane;
class Mouse;
class Stage;
class BackGround;

class Play :
	public BasePlay
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
	// 戦闘前処理
	void SetUpData(void);
	

	// 関数ポインタ
	void (Play::*draw)(void);
	void (Play::*updata)(void);
};

