#pragma once
#include "../BaseObj/Obj.h"
#include <string>
#include <map>
#include <filesystem>

class Compiler :
	public Obj
{
public:
	// �R���X�g���N�^
	Compiler();
	// �f�X�g���N�^
	~Compiler();

	// ���_�V�F�[�_�̃R���p�C��
	HRESULT ComVertex(const LPCWSTR& fileName, const LPCSTR& func, const LPCSTR& target = "vs_5_1");

	// �s�N�Z���V�F�[�_�̃R���p�C��
	HRESULT ComPixel(const LPCWSTR& fileName, const LPCSTR& func, const LPCSTR& target = "ps_5_1");

	// ���_�V�F�[�_�̎擾
	ID3DBlob* GetVertex(const LPCWSTR& path) {
		return vertex[path];
	}
	// �s�N�Z���V�F�[�_
	ID3DBlob* GetPixel(const LPCWSTR& path) {
		return pixel[path];
	}

private:
	// �t�@�C����Ԃ�
	std::wstring GetFile(const std::experimental::filesystem::path& p);

	// �f�B���N�g���̃t�@�C����
	std::vector<std::wstring> GetDirFile(const std::string& point);

	// �����񌟍�
	std::wstring SearchString(const std::wstring& m, const std::wstring & find, bool end = true);

	// �����ǂݍ���
	HRESULT Init(void);


	// �G���[
	ID3DBlob* error;

	// ���_�V�F�[�_
	std::map<std::wstring, ID3DBlob*>vertex;

	// �s�N�Z���V�F�[�_
	std::map<std::wstring, ID3DBlob*>pixel;
};

