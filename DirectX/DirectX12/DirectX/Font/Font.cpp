#include "Font.h"
#include <tchar.h>

const MAT2 mat[] = {
	{ 0, 1 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 1 }
};

// �R���X�g���N�^
Font::Font() : 
	font(nullptr), old(nullptr), size(36), name(L"�l�r �o����"), hdc(GetDC(nullptr)), code(0)
{
	tm = {};
	gm = {};
	ptr = nullptr;

	CreateFnt();
}

// �R���X�g���N�^
Font::Font(const std::wstring & path) : 
	font(nullptr), old(nullptr), size(36), name(path), hdc(GetDC(nullptr)), code(0)
{
	tm = {};
	gm = {};
	ptr = nullptr;

	CreateFnt();
}

// �f�X�g���N�^
Font::~Font()
{
	SelectObject(hdc, old);
	DeleteObject(font);
	DeleteDC(hdc);
}

// �t�H���g�̐���
HRESULT Font::CreateFnt(void)
{
	//�t�H���g�ݒ�p�\����
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
		OutputDebugString(_T("\n�t�H���g�̐����F���s\n"));
		return S_FALSE;
	}

	old = static_cast<HFONT>(SelectObject(hdc, font));

	return S_OK;
}

// �t�H���g�`��
HRESULT Font::DrawFont(void)
{
	return result;
}
