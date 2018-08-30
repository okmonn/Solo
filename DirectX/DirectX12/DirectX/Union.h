#pragma once
#include "../etc/Vector2.h"
#include "../etc/Vector3.h"
#include <d3d12.h>
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
class Texture;

class Union
{
public:
	// �f�X�g���N�^
	~Union();

	// �C���X�^���X�ϐ��̎擾
	static Union& Get(void) {
		static Union instance;
		return instance;
	}

	// �E�B���h�E�̃T�C�Y�Z�b�g
	void ChangeWindowSize(UINT x, UINT y);

	// �N���X�̃C���X�^���X��
	void Create(void);

	// ���b�Z�[�W�̊m�F
	bool CheckMsg(void);

	// �`�揀��
	void Set(void);

	// ���s
	void Do(void);

	// �L�[����
	bool CheckKey(UINT index);

	// �g���K�[�L�[����
	bool TriggerKey(UINT index);

	// �_�̕`��
	void DrawPoint(const Vec2f& pos, const Vec3f& color);

	// �摜�ǂݍ���
	void LoadImg(UINT& index, const std::string& fileName);

	// �`��
	void Draw(UINT& index, const Vec2f& pos, UINT turnX = 0, UINT turnY = 0);

	// �`��E�T�C�Y�w��
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, UINT turnX = 0, UINT turnY = 0);

	// �`��E�T�C�Y�w��E����
	void Draw(UINT& index, const Vec2f& pos, const Vec2f& size, const Vec2f& rect, const Vec2f& rectSize, UINT turnX = 0, UINT turnY = 0);

	// WAVE�ǂݍ���
	void LoadWave(UINT& index, const std::string& fileName);

	// WAVE�̍Đ�
	void PlayWave(UINT& index);

	// WAVE�̍Đ���~
	void StopWave(UINT& index);

	// MIDI�f�o�C�X���̎擾
	UINT GetMidiNum(void);

	// MIDI�X�e�[�^�X�o�C�g�̎擾
	UCHAR GetMidiState(void);

	// MIDI�f�[�^�o�C�g1�̎擾
	UCHAR GetMidiData1(void);

	// MIDI�f�[�^�o�C�g2�̎擾
	UCHAR GetMidiData2(void);

	// �f�B���N�g���̃t�@�C����
	std::vector<std::string> GetDirFile(const std::string& point);
	std::vector<std::wstring> GetDirFile(const std::wstring& point);

private:
	// �R���X�g���N�^
	Union();
	Union(const Union&) {
	}
	void operator=(const Union&) {
	}

	// �r���[�|�[�g�̃Z�b�g
	void ViewPort(void);

	// �V�U�[�̃Z�b�g
	void Scissor(void);

	// �o���A�̃Z�b�g
	void Barrier(D3D12_RESOURCE_STATES befor, D3D12_RESOURCE_STATES affter);

	// �t�@�C����Ԃ�
	std::string GetFile(const fs::path& p);
	std::wstring GetFileW(const fs::path& p);


	// ��ʃT�C�YX
	UINT x;

	// ��ʃT�C�YY
	UINT y;

	// �A���t�@�l
	float alpha;

	// ���b�Z�[�W
	MSG msg;

	// �r���[�|�[�g
	D3D12_VIEWPORT viewPort;

	// �V�U�[
	RECT scissor;

	// �o���A
	D3D12_RESOURCE_BARRIER barrier;

	// �E�B���h�E
	std::shared_ptr<Window>win;

	// �I�[�f�B�I
	std::shared_ptr<Xaudio2>audio;

	// MIDI����
	std::shared_ptr<MIDI_IN>in;

	// �C���v�b�g
	std::shared_ptr<Input>input;

#ifdef _DEBUG
	std::shared_ptr<Debug>debug;
#endif

	// �f�o�C�X
	std::shared_ptr<Device>dev;

	// �R�}���h�L���[
	std::shared_ptr<Queue>queue;

	// �R�}���h���X�g
	std::shared_ptr<List>list;

	// �X���b�v�`�F�C��
	std::shared_ptr<Swap>swap;

	// �����_�[�^�[�Q�b�g
	std::shared_ptr<Render>render;

	// �[�x�X�e���V��
	std::shared_ptr<Depth>depth;

	// �t�F���X
	std::shared_ptr<Fence>fence;

	// ���[�g�V�O�l�`��
	std::shared_ptr<Root>root;

	// �V�F�[�_�R���p�C��
	std::shared_ptr<Compiler>com;

	// �p�C�v���C��
	std::shared_ptr<Pipe>pipe;
	std::shared_ptr<Pipe>pointPipe;

	// �萔�o�b�t�@
	std::shared_ptr<Constant>constant;

	// �_
	std::shared_ptr<Point>point;

	// �e�N�X�`��
	std::shared_ptr<Texture>tex;
};
