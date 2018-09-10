// ------------------------------------------------ --------------------------------------
//�t�@�C���FWICTextureLoader12.h
//
// WIC�C���[�W��ǂݍ����Direct3D�����^�C���e�N�X�`�����쐬����@�\
//�i�\�ł���΃~�b�v�}�b�v��������������j
//
//���F�A�v���P�[�V���������ł�CoInitializeEx���Ăяo���Ă���Ɖ��肵�܂��B
//
//�����̊֐��́A�P����2D�e�N�X�`���Ƃ��č쐬���ꂽ�摜�ɕ֗��ł��B ���߂�DDSTextureLoader�͗D�ꂽ�y�ʃ����^�C�����[�_�[�ł��B
//�t��������DDS�t�@�C�����[�_�[�A���C�^�[�A����уe�N�X�`�������p�C�v���C���ɂ��ẮA
// 'Texconv'�T���v���� 'DirectXTex'���C�u�����B
//
// Copyright�ic�jMicrosoft Corporation�B �S���쌠���L�B
// MIT���C�Z���X�Ń��C�Z���X����Ă��܂��B
//
// http://go.microsoft.com/fwlink/?LinkId=248926
// http://go.microsoft.com/fwlink/?LinkID=615561
// ------------------------------------------------ --------------------------------------

#pragma once

#include <d3d12.h>
#include <stdint.h>
#include <memory>


namespace DirectX
{
	enum WIC_LOADER_FLAGS
	{
		WIC_LOADER_DEFAULT = 0,
		WIC_LOADER_FORCE_SRGB = 0x1,
		WIC_LOADER_IGNORE_SRGB = 0x2,
		WIC_LOADER_MIP_AUTOGEN = 0x4,
		WIC_LOADER_MIP_RESERVE = 0x8,
	};

	//�W���o�[�W����
	HRESULT __cdecl LoadWICTextureFromMemory(
		_In_ ID3D12Device* d3dDevice,
		_In_reads_bytes_(wicDataSize) const uint8_t* wicData,
		size_t wicDataSize,
		_Outptr_ ID3D12Resource** texture,
		std::unique_ptr<uint8_t[]>& decodedData,
		D3D12_SUBRESOURCE_DATA& subresource,
		size_t maxsize = 0);

	HRESULT __cdecl LoadWICTextureFromFile(
		_In_ ID3D12Device* d3dDevice,
		_In_z_ const wchar_t* szFileName,
		_Outptr_ ID3D12Resource** texture,
		std::unique_ptr<uint8_t[]>& decodedData,
		D3D12_SUBRESOURCE_DATA& subresource,
		size_t maxsize = 0);

	//�g����
	HRESULT __cdecl LoadWICTextureFromMemoryEx(
		_In_ ID3D12Device* d3dDevice,
		_In_reads_bytes_(wicDataSize) const uint8_t* wicData,
		size_t wicDataSize,
		size_t maxsize,
		D3D12_RESOURCE_FLAGS resFlags,
		unsigned int loadFlags,
		_Outptr_ ID3D12Resource** texture,
		std::unique_ptr<uint8_t[]>& decodedData,
		D3D12_SUBRESOURCE_DATA& subresource);

	HRESULT __cdecl LoadWICTextureFromFileEx(
		_In_ ID3D12Device* d3dDevice,
		_In_z_ const wchar_t* szFileName,
		size_t maxsize,
		D3D12_RESOURCE_FLAGS resFlags,
		unsigned int loadFlags,
		_Outptr_ ID3D12Resource** texture,
		std::unique_ptr<uint8_t[]>& decodedData,
		D3D12_SUBRESOURCE_DATA& subresource);
}