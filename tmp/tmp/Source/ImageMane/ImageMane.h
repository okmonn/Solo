#pragma once
#include <string>
#include <map>

class ImageMane
{
public:
	// �f�X�g���N�^
	~ImageMane();

	// �C���X�^���X�ϐ��̎擾
	static ImageMane& Get(void) {
		static ImageMane imstance;
		return imstance;
	}

	// �摜�̓ǂݍ���
	int LoadImg(const std::string& fileName);

	// �摜�̏���
	void DeletImg(const std::string& fileName);

private:
	// �R���X�g���N�^
	ImageMane();
	ImageMane(const ImageMane&) {
	}
	void operator=(const ImageMane&) {
	}


	// �摜�f�[�^
	std::map<std::string, int>image;
};

