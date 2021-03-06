#pragma once
#include "../etc/tstring.h"
#include "../etc/Vector2.h"
#include "../etc/Vector3.h"
#include "../DirectInput/InputData.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <DirectXMath.h>

namespace func {
	// ウィンドウサイズのセット
	void SetWindowSize(unsigned int x, unsigned int y);

	// 初期化
	void Init(void);

	// メッセージの確認
	bool CheckMsg(void);

	// ビュー行列のセット
	void ChangeView(const Vec3f& pos, const Vec3f& target, const Vec3f& up);

	// 描画準備
	void Set(void);

	// 実行
	void Do(void);

	// キー入力
	bool CheckKey(unsigned int index);

	// トリガーキー入力
	bool TriggerKey(unsigned int index);

	// α値の設定
	void SetAlpha(float alpha);

	// 点の描画
	void DrawPoint(float x, float y, float r, float g, float b);

	// ラインの描画
	void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b);

	// ボックスの描画
	void DrawBox(float x, float y, float sizeX, float sizeY, float r, float g, float b);

	// 画像読み込み
	void LoadImg(unsigned int& index, const std::string& fileName);

	// 描画
	void Draw(unsigned int& index, float x, float y, bool turnX = false, bool turnY = false);
	void Draw(unsigned int& index, float x, float y, float alpha, bool turnX = false, bool turnY = false);

	// 描画・サイズ指定
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY, bool turnX = false, bool turnY = false);
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY, float alpha, bool turnX = false, bool turnY = false);

	// 描画・サイズ指定・分割
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY,
		float rectX, float rectY, float rectSizeX, float rectSizeY, bool turnX = false, bool turnY = false);
	void Draw(unsigned int& index, float x, float y, float sizeX, float sizeY,
		float rectX, float rectY, float rectSizeX, float rectSizeY, float alpha, bool turnX = false, bool turnY = false);

	// 描画・自由変形
	void FreelyDraw(unsigned int& index, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, bool turnX = false, bool turnY = false);
	void FreelyDraw(unsigned int& index, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float alpha, bool turnX = false, bool turnY = false);

	// 描画・分割・自由変形
	void FreelyDraw(unsigned int& index, float rectX, float rectY, float rectSizeX, float rectSizeY, 
		float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, bool turnX = false, bool turnY = false);
	void FreelyDraw(unsigned int& index, float rectX, float rectY, float rectSizeX, float rectSizeY,
		float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float alpha, bool turnX = false, bool turnY = false);

	// 画像の消去
	void DeleteImg(unsigned int& index);

	// PMD読み込み
	void LoadPMD(unsigned int& index, const std::string& fileName);

	// PMD描画
	void DrawPMD(unsigned int& index);

	// PMDのボーン回転
	void RotateBorn(unsigned int& index, const std::string& name, const DirectX::XMMATRIX& matrix);

	// PMDの消去
	void DeletePMD(unsigned int& index);

	// WAVEの読み込み
	void LoadWave(unsigned int& index, const std::string fileName);

	// WAVEの再生
	void PlayWave(unsigned int& index, bool loop = false);

	// WAVEの停止
	void StopWave(unsigned int& index);

	// WAVEの消去
	void DeleteWAVE(unsigned int& index);

	// MIDIデバイスの数取得
	unsigned int GetMidiDevNum(void);

	// MIDIステータスバイトの取得
	unsigned char GetMidiState(void);

	// MIDIデータバイト1の取得
	unsigned char GetMidiData1(void);

	// MIDIデータバイト2の取得
	unsigned char GetMidiData2(void);

	// 指定したディレクトリのファイル名取得
	std::vector<std::string> GetDirFile(const std::string& path);

	// ログインユーザーネーム取得
	std::tstring GetName(void);
}
