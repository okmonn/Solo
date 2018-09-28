#include "Stage.h"
#include "StageData.h"

// �R���X�g���N�^
Stage::Stage() : 
	index(0)
{
	id.clear();
}

// �f�X�g���N�^
Stage::~Stage()
{
}

// �ǂݍ���
void Stage::LoadStage(void)
{
	if (stageData.find(index) != stageData.end())
	{
		id = stageData[index];
	}
}

// ID�̃N���A
void Stage::Clear(void)
{
	id.clear();
	id.shrink_to_fit();
}
