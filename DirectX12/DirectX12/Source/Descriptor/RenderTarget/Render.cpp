#include "render.h"
#include "../../Device/Device.h"
#include "../../Command/List/List.h"
#include "../../SwapChain/Swap.h"
#include <tchar.h>

//クリアカラー
const FLOAT color[] = {
	0.0f,
	0.0f,
	0.0f,
	0.0f
};

// コンストラクタ
Render::Render(std::weak_ptr<Device>dev, std::weak_ptr<List>list, std::weak_ptr<Swap>swap) : 
	swap(swap)
{
	this->dev  = dev; 
	this->list = list;

	CreateResource();
}

// デストラクタ
Render::~Render()
{
	for (UINT i = 0; i < resource.size(); ++i)
	{
		Release(resource[i]);
	}
	Release(heap);
}

// リソースの生成
HRESULT Render::CreateResource(void)
{
	result = CreateHeap(swap.lock()->GetBack(), D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	if (FAILED(result))
	{
		return result;
	}

	//配列のメモリ確保
	resource.resize(this->swap.lock()->GetBack());

	//レンダーターゲット設定用構造体
	D3D12_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format               = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension        = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice   = 0;
	desc.Texture2D.PlaneSlice = 0;

	//先頭ハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();

	for (UINT i = 0; i < resource.size(); ++i)
	{
		result = swap.lock()->Get()->GetBuffer(i, IID_PPV_ARGS(&resource[i]));
		if (FAILED(result))
		{
			OutputDebugString(_T("\nバッファの取得：失敗\n"));
			break;
		}

		//レンダーターゲットの生成
		dev.lock()->Get()->CreateRenderTargetView(resource[i], &desc, handle);

		//ハンドル位置の更新
		handle.ptr += size;
	}

	return result;
}

// レンダーターゲットのセット
void Render::SetRender(ID3D12DescriptorHeap* depth)
{
	//頂点ヒープの先頭ハンドルの取得
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += size * swap.lock()->Get()->GetCurrentBackBufferIndex();

	//レンダーターゲットのセット
	list.lock()->GetList()->OMSetRenderTargets(1, &handle, false, &depth->GetCPUDescriptorHandleForHeapStart());

	//レンダーターゲットのクリア
	list.lock()->GetList()->ClearRenderTargetView(handle, color, 0, nullptr);
}
