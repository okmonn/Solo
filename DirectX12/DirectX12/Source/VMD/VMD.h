#pragma once
#include "VmdDate.h"
#include <map>
#include <vector>

class VMD
{
public:
	// �R���X�g���N�^
	VMD();
	// �f�X�g���N�^
	~VMD();

	// �ǂݍ���
	int Load(unsigned int& index, const std::string& fileName);

private:
	// ���[�V����
	std::map<unsigned int*, std::vector<Motion>>motion;
};

