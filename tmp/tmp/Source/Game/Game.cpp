#include "Game.h"
#include "../Icon/Icon.h"
#include "../Scene/Title/Title.h"
#include "../Mouse/Mouse.h"
#include "DxLib.h"

// �E�B���h�E�T�C�Y
#define WINDOW_X 640
#define WINDOW_Y 480

// �R���X�g���N�^
Game::Game() :
	scene(nullptr), size({ WINDOW_X, WINDOW_Y }) , fontSize(48)
{
}

// �f�X�g���N�^
Game::~Game()
{
}

// �V�[���ڍs
void Game::ChangeScene(Scene * scene)
{
	this->scene.reset(scene);
}

// ������
void Game::Init(void)
{
	//�O���t�B�b�N���[�h�̐ݒ�
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	//true:window�@false:�ٽ�ذ�
	ChangeWindowMode(true);

	// �A�C�R���Z�b�g
	SetWindowIconID(ICON_ID);

	//window�e�L�X�g�̐ݒ�
	SetWindowText(_T("1601271_���ɒj"));

	//Dxlib�̏�����
	if (DxLib_Init() == -1)
	{
		return;
	}

	// �t�H���g�ǉ�
	AddFontResourceEx("Material/font/GN-Kin-iro_SansSerif.ttf", FR_PRIVATE, NULL);
	ChangeFont("GN-���񂢂�T���Z���t", DX_CHARSET_DEFAULT);
	SetFontSize(fontSize);

	//�}�E�X�J�[�\���̕\��
	SetMouseDispFlag(true);

	//�ЂƂ܂��ޯ��ޯ̧�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//�����V�[��
	ChangeScene(new Title());
}

// �`��
void Game::Draw(void)
{
	//��ʏ���
	ClsDrawScreen();

	scene->Draw();

	//����ʂ�\��ʂɏu�ԃR�s�[
	ScreenFlip();
}

// ����
void Game::UpData(void)
{
	Draw();

	Mouse::Get().UpData();

	scene->UpData();
}


// ����
void Game::Run(void)
{
	Init();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		UpData();
	}

	End();
}

// �I������
void Game::End(void)
{
	DxLib_End();
}
