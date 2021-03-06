#pragma once
#include "../etc/tstring.h"
#include "../etc/Vector2.h"
#include "../etc/Vector3.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

namespace fs = std::experimental::filesystem;

class Window;
class Xaudio2;
class MIDI_IN;
class Input;
#ifdef _DEBUG
class Debug;
#endif
class Device;
class Queue;
class List;
class Swap;
class Render;
class Depth;
class Fence;
class Root;
class Compiler;
class Pipe;
class Constant;
class Point;
class Line;
class Box;
class Texture;
class VMD;
class PMD;

class Union
{
public:
	// デストラクタ
	~Union();

	// インスタンス変数の取得
	static Union& Get(void) {
		static Union instance;
		return instance;
	}

	// ウィンドウのサイズセット
	void ChangeWindowSize(UINT x, UINT y);

	// クラスのインスタンス化
	void Create(void);

	// メッセージの確認
	bool CheckMsg(void);

	// ビュー行列のセット
	void ChangeView(const Vec3f& pos, const Vec3f& target, const Vec3f& up);

	// 描画準備
	void Set(void);

	// 実行
	void Do(void);

	// キー入力
	bool CheckKey(UINT index);

	// トリガーキー入力
	bool TriggerKey(UINT index);

	// α値の変更
	void SetAlpha(float alpha) {
		this->alpha = alpha;
	}

	// 点の描画
	void DrawPoint(const Vec2f& pos, const Vec3f& color);

	// ラインの描画
	void DrawLine(const Vec2f& pos1, const Vec2f& pos2, const Vec3f& color);

	// ボックスの描画
	void DrawBox(const Vec2f& pos, const Vec2f& size, const Vec3f& color);

	// 画像読み込み
	void LoadImg(UINT& index, const std::string& fileName);

	// 描画
	void Draw(UINT& index, const Vec2f& pos, UINT turnX, UINT turnY);
	void Draw(UINT& index, const Vec2f& pos, float alpha, UINT turnX, UINT turnY);

	// 描画・サイズ指定
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, UINT turnX, UINT turnY);
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, float alpha, UINT turnX, UINT turnY);

	// 描画・サイズ指定・分割
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, const Vec2f& rect, const Vec2f& rectSize, UINT turnX, UINT turnY);
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, const Vec2f& rect, const Vec2f& rectSize, float alpha, UINT turnX, UINT turnY);

	// 描画・自由変形
	void FreelyDraw(UINT& index, const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const Vec2f& pos4, UINT turnX, UINT turnY);
	void FreelyDraw(UINT& index, const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const Vec2f& pos4, float alpha, UINT turnX, UINT turnY);

	// 描画・分割・自由変形
	void FreelyDraw(UINT& index, const Vec2f& rectPos, const Vec2f& rectSize, const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const Vec2f& pos4, UINT turnX, UINT turnY);
	void FreelyDraw(UINT& index, const Vec2f& rectPos, const Vec2f& rectSize, const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const Vec2f& pos4, float alpha, UINT turnX, UINT turnY);

	// 画像の消去
	void DeleteImg(UINT& index);

	// VMD読み込み
	void LoadVMD(UINT& index, const std::string& fileName);

	// PMD読み込み
	void LoadPMD(UINT& index, const std::string& fileName);

	// PMD描画
	void DrawPMD(UINT& index);

	// PMDのボーン回転
	void RotateBorn(UINT& index, const std::string& name, const DirectX::XMMATRIX& matrix);

	// PMDの消去
	void DeletePMD(UINT& index);

	// WAVE読み込み
	void LoadWave(UINT& index, const std::string& fileName);

	// WAVEの再生
	void PlayWave(UINT& index, bool loop);

	// WAVEの再生停止
	void StopWave(UINT& index);

	// WAVEの消去
	void DeleteWAVE(UINT& index);

	// MIDIデバイス数の取得
	UINT GetMidiNum(void);

	// MIDIステータスバイトの取得
	UCHAR GetMidiState(void);

	// MIDIデータバイト1の取得
	UCHAR GetMidiData1(void);

	// MIDIデータバイト2の取得
	UCHAR GetMidiData2(void);

	// ディレクトリのファイル列挙
	std::vector<std::string> GetDirFile(const std::string& point);

private:
	// コンストラクタ
	Union();
	Union(const Union&) {
	}
	void operator=(const Union&) {
	}

	// ルートシグネチャの生成
	void CreateRoot(void);

	// パイプラインの生成
	void CreatePipeLine(void);

	// ビューポートのセット
	void ViewPort(void);

	// シザーのセット
	void Scissor(void);

	// バリアのセット
	void Barrier(D3D12_RESOURCE_STATES befor, D3D12_RESOURCE_STATES affter);

	// ファイルを返す
	std::string GetFile(const fs::path& p);

	// 画像アドレスの消去
	void EraseImg(void);


	// 画面サイズX
	UINT x;

	// 画面サイズY
	UINT y;

	// アルファ値
	float alpha;

	// メッセージ
	MSG msg;

	// ビューポート
	D3D12_VIEWPORT viewPort;

	// シザー
	RECT scissor;

	// バリア
	D3D12_RESOURCE_BARRIER barrier;

	// 破棄アドレス
	std::vector<UINT*>erase;

	// ウィンドウ
	std::shared_ptr<Window>win;

	// オーディオ
	std::shared_ptr<Xaudio2>audio;

	// MIDI入力
	std::shared_ptr<MIDI_IN>in;

	// インプット
	std::shared_ptr<Input>input;

#ifdef _DEBUG
	std::shared_ptr<Debug>debug;
#endif

	// デバイス
	std::shared_ptr<Device>dev;

	// コマンドキュー
	std::shared_ptr<Queue>queue;

	// コマンドリスト
	std::shared_ptr<List>list;

	// スワップチェイン
	std::shared_ptr<Swap>swap;

	// レンダーターゲット
	std::shared_ptr<Render>render;

	// 深度ステンシル
	std::shared_ptr<Depth>depth;

	// フェンス
	std::shared_ptr<Fence>fence;

	// ルートシグネチャ
	std::shared_ptr<Root>pointRoot;
	std::shared_ptr<Root>texRoot;
	std::shared_ptr<Root>modelRoot;

	// シェーダコンパイル
	std::shared_ptr<Compiler>com;

	// パイプライン
	std::shared_ptr<Pipe>pointPipe;
	std::shared_ptr<Pipe>linePipe;
	std::shared_ptr<Pipe>boxPipe;
	std::shared_ptr<Pipe>texPipe;
	std::shared_ptr<Pipe>modelPipe;

	// 定数バッファ
	std::shared_ptr<Constant>constant;

	// 点
	std::shared_ptr<Point>point;

	// ライン
	std::shared_ptr<Line>line;

	// ボックス
	std::shared_ptr<Box>box;

	// テクスチャ
	std::shared_ptr<Texture>tex;

	// VMD
	std::shared_ptr<VMD>vmd;

	// PMD
	std::shared_ptr<PMD>pmd;
};
