#pragma once
#include "../Descriptor/Descriptor.h"
#include <string>

class Font :
	public Descriptor
{
public:
	// �R���X�g���N�^
	Font();
	Font(const std::wstring& path);
	// �f�X�g���N�^
	~Font();

	// �t�H���g�T�C�Y�̎擾
	LONG GetSize(void) const {
		return size;
	}
	// �t�H���g�T�C�Y�̃Z�b�g
	void SetSize(const LONG& i) {
		size = i;
	}

private:
	// �t�H���g�̐���
	HRESULT CreateFnt(void);

	// �t�H���g�`��
	HRESULT DrawFont(void);


	// �t�H���g
	HFONT font;

	// �O�̃t�H���g
	HFONT old;

	// �t�H���g�T�C�Y
	LONG size;

	// �t�H���g��
	std::wstring name;

	// 
	HDC hdc;

	// �����ݕ����ԍ�
	UINT code;

	// 
	TEXTMETRIC tm;

	// 
	GLYPHMETRICS gm;

	// �A�h���X
	BYTE* ptr;
};

