#include <d3dcompiler.h>
#include "Root.h"
#include "Device.h"
#include <tchar.h>

#pragma comment (lib, "d3dcompiler.lib")

// �R���X�g���N�^
Root::Root(std::weak_ptr<Device>dev) :
	dev(dev), signature(nullptr), error(nullptr), root(nullptr)
{
	Serialize();
	CreateRoot();
}

// �f�X�g���N�^
Root::~Root()
{
	Release(root);
	Release(error);
	Release(signature);
}

// �V���A���C�Y
HRESULT Root::Serialize(void)
{
	// �f�B�X�N���v�^�����W�̐ݒ�.
	D3D12_DESCRIPTOR_RANGE range[2];
	SecureZeroMemory(&range, sizeof(range));

	//���[�g�p�����[�^�̐ݒ�.
	D3D12_ROOT_PARAMETER param[2];
	SecureZeroMemory(&param, sizeof(param));

	//�萔�o�b�t�@�p�EWVP
	range[0].RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	range[0].NumDescriptors                    = 1;
	range[0].BaseShaderRegister                = 0;
	range[0].RegisterSpace                     = 0;
	range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	param[0].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	param[0].ShaderVisibility                    = D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_VERTEX;
	param[0].DescriptorTable.NumDescriptorRanges = 1;
	param[0].DescriptorTable.pDescriptorRanges   = &range[0];

	//�e�N�X�`���p
	range[1].RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	range[1].NumDescriptors                    = 1;
	range[1].BaseShaderRegister                = 0;
	range[1].RegisterSpace                     = 0;
	range[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	param[1].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	param[1].ShaderVisibility                    = D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL;
	param[1].DescriptorTable.NumDescriptorRanges = 1;
	param[1].DescriptorTable.pDescriptorRanges   = &range[1];

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
	desc.NumParameters     = _countof(param);
	desc.pParameters       = param;
	desc.NumStaticSamplers = 1;
	desc.pStaticSamplers   = &sampler;
	desc.Flags             = D3D12_ROOT_SIGNATURE_FLAGS::D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	result = D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION::D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
	if (FAILED(result))
	{
		OutputDebugString(_T("\n�V���A���C�Y�F���s\n"));
	}

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
