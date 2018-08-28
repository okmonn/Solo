#include "Func.h"
#include "DirectX/Union.h"

// �E�B���h�E�T�C�Y�̃Z�b�g
void func::SetWindowSize(unsigned int x, unsigned int y)
{
	Union::Get().ChangeWindowSize(x, y);
}

// ������
void func::Init(void)
{
	Union::Get().Create();
}

// ���b�Z�[�W�̊m�F
bool func::CheckMsg(void)
{
	return Union::Get().CheckMsg();
}

// �`�揀��
void func::Set(void)
{
	Union::Get().Set();
}

// ���s
void func::Do(void)
{
	Union::Get().Do();
}

// �L�[����
bool func::CheckKey(unsigned int index)
{
	return Union::Get().CheckKey(index);
}

// �g���K�[�L�[����
bool func::TriggerKey(unsigned int index)
{
	return Union::Get().TriggerKey(index);
}

// �摜�ǂݍ���
void func::LoadImg(unsigned int & index, const std::string & fileName)
{
	Union::Get().LoadImg(index, fileName);
}

// �`��
void func::Draw(unsigned int & index, float x, float y, bool turnX, bool turnY)
{
	Union::Get().Draw(index, { x, y }, turnX, turnY);
}

// �`��E�T�C�Y�w��
void func::Draw(unsigned int & index, float x, float y, float sizeX, float sizeY, bool turnX, bool turnY)
{
	Union::Get().Draw(index, { x, y }, { sizeX, sizeY }, turnX, turnY);
}

// �`��E�T�C�Y�w��E����
void func::Draw(unsigned int & index, float x, float y, float sizeX, float sizeY, float rectX, float rectY, float rectSizeX, float rectSizeY, bool turnX, bool turnY)
{
	Union::Get().Draw(index, { x, y }, { sizeX, sizeY }, { rectX, rectY }, { rectSizeX, rectSizeY }, turnX, turnY);
}

// WAVE�̓ǂݍ���
void func::LoadWave(unsigned int& index, const std::string fileName)
{
	Union::Get().LoadWave(index, fileName);
}

// WAVE�̍Đ�
void func::PlayWave(unsigned int& index)
{
	Union::Get().PlayWave(index);
}

// WAVE�̒�~
void func::StopWave(unsigned int& index)
{
	Union::Get().StopWave(index);
}

// MIDI�f�o�C�X�̐��擾
unsigned int func::GetMidiDevNum(void)
{
	return Union::Get().GetMidiNum();
}

// MIDI�X�e�[�^�X�o�C�g�̎擾
unsigned char func::GetMidiState(void)
{
	return Union::Get().GetMidiState();
}

// MIDI�f�[�^�o�C�g1�̎擾
unsigned char func::GetMidiData1(void)
{
	return Union::Get().GetMidiData1();
}

// MIDI�f�[�^�o�C�g2�̎擾
unsigned char func::GetMidiData2(void)
{
	return Union::Get().GetMidiData2();
}

// �w�肵���f�B���N�g���̃t�@�C�����擾
std::vector<std::string> func::GetDirFile(const std::string & path)
{
	return Union::Get().GetDirFile(path);
}
