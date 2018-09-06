#pragma once
#include "Obj.h"
#include <dxgi1_4.h>
#include <memory>

class Window;
class Queue;

class Swap :
	public Obj
{
public:
	// �R���X�g���N�^
	Swap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue);
	// �f�X�g���N�^
	~Swap();

	// ���E�\�̓���ւ�
	void Present(void);

	// �X���b�v�`�F�C���̎擾
	IDXGISwapChain3* Get(void) const {
		return swap;
	}

	// �o�b�N�o�b�t�@�̎擾
	UINT GetBack(void) const {
		return bufferCnt;
	}

private:
	// �t�@�N�g���[�̐���
	HRESULT CreateFactory(void);

	// �X���b�v�`�F�C���̐���
	HRESULT CreateSwap(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �R�}���h�L���[
	std::weak_ptr<Queue>queue;

	// �t�@�N�g���[
	IDXGIFactory4* factory;

	// �X���b�v�`�F�C��
	IDXGISwapChain3* swap;

	// �o�b�N�o�b�t�@��
	UINT bufferCnt;
};

