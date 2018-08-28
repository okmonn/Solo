#include "Font.h"
#include "../Device.h"
#include "../Command/List.h"
#include <tchar.h>

const MAT2 mat = { 
	{ 0, 1 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 1 } 
};

// コンストラクタ
Font::Font(std::weak_ptr<Device>dev, std::weak_ptr<List>list) :
	font(nullptr), old(nullptr), size(36), weight(500), level(16), name(L"ＭＳ Ｐ明朝"), hdc(GetDC(nullptr))
{
	this->dev = dev;
	this->list = list;

	tm = {};
	GetTextMetrics(hdc, &tm);
	gm = {};

	bmp = {};

	CreateFnt();
}

// コンストラクタ
Font::Font(const std::wstring & path, std::weak_ptr<Device>dev, std::weak_ptr<List>list) :
	font(nullptr), old(nullptr), size(36), weight(500), level(16), name(path), hdc(GetDC(nullptr))
{
	this->dev = dev;
	this->list = list;

	tm = {};
	GetTextMetrics(hdc, &tm);
	gm = {};

	CreateFnt();
}

// デストラクタ
Font::~Font()
{
	Release(bmp.con.resource);
	Release(bmp.con.heap);

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
		0, 0, 0, 
		weight, 0, 0, 0, 
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

	DrawFont();

	return S_OK;
}

// ヒープの生成
HRESULT Font::CreateConHeap(void)
{
	//ヒープ設定用構造体
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask       = 0;
	desc.NumDescriptors = 1;
	desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	result = dev.lock()->Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&bmp.con.heap));
	if (FAILED(result))
	{
		OutputDebugString(_T("\nフォントのヒープの生成：失敗\n"));
	}

	return result;
}

// リソースの生成
HRESULT Font::CreateConResource(void)
{
	//プロパティ設定用構造体の設定
	D3D12_HEAP_PROPERTIES prop = {};
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_CUSTOM;
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_L0;
	prop.CreationNodeMask     = 1;
	prop.VisibleNodeMask      = 1;

	//リソース設定用構造体の設定
	D3D12_RESOURCE_DESC desc = {};
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Width            = bmp.x;
	desc.Height           = bmp.y;
	desc.DepthOrArraySize = 1;
	desc.MipLevels        = 1;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	desc.SampleDesc.Count = 1;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;

	result = dev.lock()->Get()->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&bmp.con.resource));
	if (FAILED(result))
	{
		OutputDebugString(_T("\nフォントのリソースの生成：失敗\n"));
	}

	return result;
}

// シェーダリソースビューの生成
HRESULT Font::CreateShaderView(void)
{
	//シェーダリソースビュー設定用構造体
	D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format                    = bmp.con.resource->GetDesc().Format;
	desc.ViewDimension             = D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels       = 1;
	desc.Texture2D.MostDetailedMip = 0;
	desc.Shader4ComponentMapping   = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	dev.lock()->Get()->CreateShaderResourceView(bmp.con.resource, &desc, bmp.con.heap->GetCPUDescriptorHandleForHeapStart());

	return result;
}

// フォント描画
HRESULT Font::DrawFont(void)
{
	//文字の番号の取得
	UINT code = static_cast<UINT>('a');

	//サイズ取得
	DWORD size = GetGlyphOutlineW(hdc, code, GGO_GRAY4_BITMAP, &gm, 0, nullptr, &mat);

	//配列のメモリ確保
	std::vector<BYTE>dummy(size);
	bmp.image.resize(size);

	//データを格納
	GetGlyphOutlineW(hdc, code, GGO_GRAY4_BITMAP, &gm, size, dummy.data(), &mat);

	UINT wedth = (gm.gmBlackBoxX + 3) / 4 * 4;
	DWORD alpha = 0;

	for (UINT y = 0; y < gm.gmBlackBoxY; ++y)
	{
		for (UINT x = 0; x < wedth; ++x)
		{
			alpha = dummy[y * wedth + x] * 255 / level;
			bmp.image[y * wedth + x] = static_cast<BYTE>((alpha << 24) | 0x00ffffff);
		}
	}

	result = CreateConHeap();
	result = CreateConResource();
	result = CreateShaderView();

	return result;
}
