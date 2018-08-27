#include "Font.h"
#include <tchar.h>

const MAT2 mat[] = {
	{ 0, 1 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 1 }
};

// コンストラクタ
Font::Font() : 
	font(nullptr), old(nullptr), size(36), name(L"ＭＳ Ｐ明朝"), hdc(GetDC(nullptr)), code(0)
{
	tm = {};
	gm = {};
	ptr = nullptr;

	CreateFnt();
}

// コンストラクタ
Font::Font(const std::wstring & path) : 
	font(nullptr), old(nullptr), size(36), name(path), hdc(GetDC(nullptr)), code(0)
{
	tm = {};
	gm = {};
	ptr = nullptr;

	CreateFnt();
}

// デストラクタ
Font::~Font()
{
	SelectObject(hdc, old);
	DeleteObject(font);
	DeleteDC(hdc);
}

// フォントの生成
HRESULT Font::CreateFnt(void)
{
	//フォント設定用構造体
	LOGFONT log = { 
		size, 
		0, 0, 0, 0, 0, 0, 0, 
		SHIFTJIS_CHARSET, 
		OUT_TT_ONLY_PRECIS, 
		CLIP_DEFAULT_PRECIS, 
		PROOF_QUALITY, 
		DEFAULT_PITCH | FF_MODERN,
	};
	for (UINT i = 0; i < name.size(); ++i)
	{
		log.lfFaceName[i] = name[i];
	}

	font = CreateFontIndirect(&log);
	if (font == nullptr)
	{
		OutputDebugString(_T("\nフォントの生成：失敗\n"));
		return S_FALSE;
	}

	old = static_cast<HFONT>(SelectObject(hdc, font));

	return S_OK;
}

// フォント描画
HRESULT Font::DrawFont(void)
{
	return result;
}
