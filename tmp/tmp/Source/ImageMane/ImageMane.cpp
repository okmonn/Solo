#include "ImageMane.h"
#include "DxLib.h"

// �R���X�g���N�^
ImageMane::ImageMane()
{
	image.clear();
}

// �f�X�g���N�^
ImageMane::~ImageMane()
{
	for (auto itr = image.begin(); itr != image.end(); ++itr)
	{
		DeleteGraph(itr->second);
	}
}

// �摜�̓ǂݍ���
int ImageMane::LoadImg(const std::string & fileName)
{
	if (image.find(fileName) != image.end())
	{
		return image[fileName];
	}
	
	return image[fileName] = LoadGraph(fileName.c_str());
}

// �摜�̏���
void ImageMane::DeletImg(const std::string & fileName)
{
	if (image.find(fileName) != image.end())
	{
		DeleteGraph(image[fileName]);
	}
}
