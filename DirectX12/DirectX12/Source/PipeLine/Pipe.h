#pragma once
#include "../BaseObj/Obj.h"
#include <memory>

class Device;
class Swap;
class Root;
class Compiler;

class Pipe :
	public Obj
{
public:
	// コンストラクタ
	Pipe(const LPCWSTR& path, std::weak_ptr<Device>dev, std::weak_ptr<Swap>swap, std::weak_ptr<Root>root, std::weak_ptr<Compiler>com, bool depth = false);
	// デストラクタ
	~Pipe();

	// パイプラインの取得
	ID3D12PipelineState* Get(void) const {
		return pipe;
	}

	// パイプラインの生成
	HRESULT CreatePipe(const D3D12_INPUT_ELEMENT_DESC* input, UINT num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type);

private:
	// デバイス
	std::weak_ptr<Device>dev;

	// スワップチェイン
	std::weak_ptr<Swap>swap;

	// ルートシグネチャ
	std::weak_ptr<Root>root;

	// シェーダコンパイラー
	std::weak_ptr<Compiler>com;

	// パイプライン
	ID3D12PipelineState* pipe;

	// パス
	LPCWSTR path;

	// 深度ステンシル許可フラグ
	bool depth;
};

