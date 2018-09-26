#pragma once
#include <string>
#include <map>

class ImageMane
{
public:
	// デストラクタ
	~ImageMane();

	// インスタンス変数の取得
	static ImageMane& Get(void) {
		static ImageMane imstance;
		return imstance;
	}

	// 画像の読み込み
	int LoadImg(const std::string& fileName);

	// 画像の消去
	void DeletImg(const std::string& fileName);

private:
	// コンストラクタ
	ImageMane();
	ImageMane(const ImageMane&) {
	}
	void operator=(const ImageMane&) {
	}


	// 画像データ
	std::map<std::string, int>image;
};

