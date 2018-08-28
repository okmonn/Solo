#pragma once
#include "../Descriptor/Descriptor.h"
#include "../../etc/Typedef.h"
#include <map>
#include <vector>
#include <string>

class Font :
	public Descriptor
{
	// 定数バッファ
	struct Con {
		//ヒープ
		ID3D12DescriptorHeap* heap;
		//リソース
		ID3D12Resource* resource;
	};
	// BMPデータ
	struct BMP {
		//データ
		std::vector<BYTE>data;
		//サイズX
		LONG x;
		//サイズY
		LONG y;
		//頂点データ
		std::vector<Vertex>vertex;
		//リソース
		ID3D12Resource* resource;
		//頂点バッファビュー
		D3D12_VERTEX_BUFFER_VIEW view;
		//送信データ
		UINT8* data;
		//定数バッファ
		Con con;
	};

public:
	// コンストラクタ
	Font(std::weak_ptr<Device>dev, std::weak_ptr<List>list);
	Font(const std::wstring& path, std::weak_ptr<Device>dev, std::weak_ptr<List>list);
	// デストラクタ
	~Font();

	// フォントサイズの取得
	LONG GetSize(void) const {
		return size;
	}
	// フォントサイズのセット
	void SetSize(const LONG& i) {
		size = i;
	}

	// フォントの太さの取得
	LONG GetWeight(void) const {
		return weight;
	}
	// フォントの太さのセット
	void SetWeight(const LONG& i) {
		weight = i;
	}

private:
	// フォントの生成
	HRESULT CreateFnt(void);

	// ヒープの生成
	HRESULT CreateConHeap(void);

	// リソースの生成
	HRESULT CreateConResource(void);

	// シェーダリソースビューの生成
	HRESULT CreateShaderView(void);

	// フォント描画
	HRESULT DrawFont(void);


	// フォント
	HFONT font;

	// 前のフォント
	HFONT old;

	// フォントサイズ
	LONG size;

	// フォントの太さ
	LONG weight;

	// フォント名
	std::wstring name;

	// 
	HDC hdc;

	// 
	TEXTMETRIC tm;

	// 
	GLYPHMETRICS gm;

	// 
	BMP bmp;
};

