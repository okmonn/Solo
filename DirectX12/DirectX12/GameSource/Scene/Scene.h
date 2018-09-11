#pragma once
#include "../../Source/etc/Vector2.h"
#include <map>
#include <string>

class Scene
{
public:
	// コンストラクタ
	Scene();
	// デストラクタ
	virtual ~Scene();

	// 描画
	virtual void Draw(void) = 0;
	// 処理
	virtual void UpData(void) = 0;

protected:
	// 画像データの追加
	void AddImg(const std::string& fileName);

	// 描画
	void Draw(const std::string& name, const Vec2f& pos, bool turnX = false, bool turnY = false);

	// 描画・サイズ指定
	void Draw(const std::string& name, const Vec2f& pos, const Vec2f& size, bool turnX = false, bool turnY = false);

	// 画像データ
	std::map<std::string, unsigned int>data;
};
