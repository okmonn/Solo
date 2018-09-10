#include <d3dcompiler.h>
#include "Compiler.h"
#include <tchar.h>

#pragma comment (lib, "d3dcompiler.lib")

// �R���X�g���N�^
Compiler::Compiler() :
	error(nullptr)
{
	vertex.clear();
	pixel.clear();

	Init();
}

// �f�X�g���N�^
Compiler::~Compiler()
{
	for (auto itr = vertex.begin(); itr != vertex.end(); ++itr)
	{
		Release(itr->second);
	}
	for (auto itr = pixel.begin(); itr != pixel.end(); ++itr)
	{
		Release(itr->second);
	}
	Release(error);
}

// ���_�V�F�[�_�̃R���p�C��
HRESULT Compiler::ComVertex(const LPCWSTR& fileName, const LPCSTR& func, const LPCSTR& target)
{
	result = D3DCompileFromFile(fileName, nullptr, nullptr, func, target, D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertex[fileName], &error);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n���_�V�F�[�_�̃R���p�C���F���s\n"));
	}

	return result;
}

// �s�N�Z���V�F�[�_�̃R���p�C��
HRESULT Compiler::ComPixel(const LPCWSTR& fileName, const LPCSTR& func, const LPCSTR& target)
{
	result = D3DCompileFromFile(fileName, nullptr, nullptr, func, target, D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixel[fileName], &error);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�s�N�Z���V�F�[�_�̃R���p�C���F���s\n"));
	}

	return result;
}

// �t�@�C����Ԃ�
std::wstring Compiler::GetFile(const std::experimental::filesystem::path & p)
{
	std::wstring m;
	//�t�@�C���̏ꍇ
	if (std::experimental::filesystem::is_regular_file(p))
	{
		m = p.filename().wstring();
	}
	else if (std::experimental::filesystem::is_directory(p))
	{
		m = p.wstring();
	}

	return m;
}

// �f�B���N�g���̃t�@�C����
std::vector<std::wstring> Compiler::GetDirFile(const std::string & point)
{
	//�񋓂̋N�_
	std::experimental::filesystem::path p(point.c_str());

	std::vector<std::wstring>fileName;

	for (auto& i : std::experimental::filesystem::recursive_directory_iterator(p))
	{
		auto tmp = GetFile(i);
		if (tmp.size() > 0)
		{
			fileName.push_back(tmp);
		}
	}

	return fileName;
}

// �����񌟍�
std::wstring Compiler::SearchString(const std::wstring& m, const std::wstring & find, bool end)
{
	if (end == false)
	{
		UINT start = m.find_first_of(find);
		auto dummy = m.substr(start + 1, m.size() - start);
		return dummy;
	}
	else if (end == true)
	{
		UINT start = m.find_last_of(find);
		auto dummy = m.substr(start + 1, m.size());
		return dummy;
	}
	
	return std::wstring();
}

// �����ǂݍ���
HRESULT Compiler::Init(void)
{
	auto file = GetDirFile("Source/Shader");
	for (UINT i = 0; i < file.size(); ++i)
	{
		std::wstring name = L"Source/Shader/" + file[i];
		result = ComVertex(name.c_str(), "VS");
		if (FAILED(result))
		{
			break;
		}
		result = ComPixel(name.c_str(), "PS");
		if (FAILED(result))
		{
			break;
		}
	}

	return result;
}
