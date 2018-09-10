#include "Device.h"
#include <tchar.h>

// �@�\���x���ꗗ
D3D_FEATURE_LEVEL levels[] =
{
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0,
};

// �R���X�g���N�^
Device::Device() : 
	dev(nullptr), level(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1)
{
	CreateDev();
}

// �f�X�g���N�^
Device::~Device()
{
	Release(dev);
}

// �f�o�C�X�̐���
HRESULT Device::CreateDev(void)
{
	for (auto& i : levels)
	{
		result = D3D12CreateDevice(nullptr, i, IID_PPV_ARGS(&dev));
		if (result == S_OK)
		{
			level = i;
			break;
		}
	}

	if (FAILED(result))
	{
		OutputDebugString(_T("\n�f�o�C�X�̐����F���s\n"));
	}

	return result;
}
