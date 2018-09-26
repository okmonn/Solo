#include "ImageMane.h"
#include "DxLib.h"

// コンストラクタ
ImageMane::ImageMane()
{
	image.clear();
}

// デストラクタ
ImageMane::~ImageMane()
{
	for (auto itr = image.begin(); itr != image.end(); ++itr)
	{
		DeleteGraph(itr->second);
	}
}

// 画像の読み込み
int ImageMane::LoadImg(const std::string & fileName)
{
	if (image.find(fileName) != image.end())
	{
		return image[fileName];
	}
	
	return image[fileName] = LoadGraph(fileName.c_str());
}

// 画像の消去
void ImageMane::DeletImg(const std::string & fileName)
{
	if (image.find(fileName) != image.end())
	{
		DeleteGraph(image[fileName]);
	}
}
