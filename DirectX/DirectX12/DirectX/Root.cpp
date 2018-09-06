#include <d3dcompiler.h>
#include "Root.h"
#include "Device.h"
#include <tchar.h>

// �R���X�g���N�^
Root::Root(std::weak_ptr<Device>dev) :
	dev(dev), signature(nullptr), error(nullptr), root(nullptr)
{
}

// �f�X�g���N�^
Root::~Root()
{
	Release(root);
	Release(error);
	Release(signature);
}

// ���[�g�V�O�l�`���̐���
HRESULT Root::CreateRoot(const D3D12_ROOT_PARAMETER * param, UINT num)
{
	//�ÓI�T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC sampler = {};
	sampler.Filter           = D3D12_FILTER::D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	sampler.AddressU         = D3D12_TEXTURE_ADDRESS_MODE::D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler.AddressV         = D3D12_TEXTURE_ADDRESS_MODE::D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler.AddressW         = D3D12_TEXTURE_ADDRESS_MODE::D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler.MipLODBias       = 0;
	sampler.MaxAnisotropy    = 0;
	sampler.ComparisonFunc   = D3D12_COMPARISON_FUNC::D3D12_COMPARISON_FUNC_NEVER;
	sampler.BorderColor      = D3D12_STATIC_BORDER_COLOR::D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	sampler.MinLOD           = 0.0f;
	sampler.MaxLOD           = D3D12_FLOAT32_MAX;
	sampler.ShaderRegister   = 0;
	sampler.RegisterSpace    = 0;
	sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL;

	//���[�g�V�O�l�`���ݒ�p�\���̂̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC desc = {};
	desc.NumParameters     = num;
	desc.pParameters       = param;
	desc.NumStaticSamplers = 1;
	desc.pStaticSamplers   = &sampler;
	desc.Flags             = D3D12_ROOT_SIGNATURE_FLAGS::D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	result = D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION::D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�V���A���C�Y�F���s\n"));
		return result;
	}

	result = CreateRoot();

	return result;
}

// ���[�g�V�O�l�`���̐���
HRESULT Root::CreateRoot(void)
{
	result = dev.lock()->Get()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(result))
	{
		OutputDebugString(_T("\n���[�g�V�O�l�`���̐����F���s\n"));
	}

	return result;
}
