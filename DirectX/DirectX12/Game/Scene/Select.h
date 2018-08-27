#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

class Select :
	public Scene
{
public:
	// �R���X�g���N�^
	Select();
	// �f�X�g���N�^
	~Select();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �z��ɒǉ�
	void AddFileName(const fs::path& path);

	// �f�B���N�g���̓ǂݍ���
	void LoadDir(const std::string& path);

	// �L�[����
	void Key(void);

	// MIDI����
	void Midi(void);


	// �f�B���N�g�����̃t�@�C����
	std::vector<std::string>fileName;

	// �֐��|�C���^
	void (Select::*func)(void);
};

