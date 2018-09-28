#include "Stage.h"
#include "StageData.h"

// コンストラクタ
Stage::Stage() : 
	index(0)
{
	id.clear();
}

// デストラクタ
Stage::~Stage()
{
}

// 読み込み
void Stage::LoadStage(void)
{
	if (stageData.find(index) != stageData.end())
	{
		id = stageData[index];
	}
}

// IDのクリア
void Stage::Clear(void)
{
	id.clear();
	id.shrink_to_fit();
}
