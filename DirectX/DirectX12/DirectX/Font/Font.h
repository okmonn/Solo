#pragma once
#include "../Descriptor/Descriptor.h"
#include <string>

class Font :
	public Descriptor
{
public:
	// コンストラクタ
	Font();
	Font(const std::wstring& path);
	// デストラクタ
	~Font();

	// フォントサイズの取得
	LONG GetSize(void) const {
		return size;
	}
	// フォントサイズのセット
	void SetSize(const LONG& i) {
		size = i;
	}

private:
	// フォントの生成
	HRESULT CreateFnt(void);

	// フォント描画
	HRESULT DrawFont(void);


	// フォント
	HFONT font;

	// 前のフォント
	HFONT old;

	// フォントサイズ
	LONG size;

	// フォント名
	std::wstring name;

	// 
	HDC hdc;

	// 書込み文字番号
	UINT code;

	// 
	TEXTMETRIC tm;

	// 
	GLYPHMETRICS gm;

	// アドレス
	BYTE* ptr;
};

