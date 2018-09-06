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

// �r���[�s��̃Z�b�g
void func::ChangeView(const Vec3f & pos, const Vec3f & target, const Vec3f & up)
{
	Union::Get().ChangeView(pos, target, up);
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

// ���l�̐ݒ�
void func::SetAlpha(float alpha)
{
	Union::Get().SetAlpha(alpha);
}

// �_�̕`��
void func::DrawPoint(float x, float y, float r, float g, float b)
{
	Union::Get().DrawPoint({ x, y }, { r, g, b });
}

// ���C���̕`��
void func::DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b)
{
	Union::Get().DrawLine({ x1, y1 }, { x2, y2 }, { r, g, b });
}

// �{�b�N�X�̕`��
void func::DrawBox(float x, float y, float sizeX, float sizeY, float r, float g, float b)
{
	Union::Get().DrawBox({ x, y }, { sizeX, sizeY },  { r, g, b });
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

// �摜�̏���
void func::DeleteImg(unsigned int & index)
{
	Union::Get().DeleteImg(index);
}

// PMD�ǂݍ���
void func::LoadPMD(unsigned int & index, const std::string & fileName)
{
	Union::Get().LoadPMD(index, fileName);
}

// PMD�`��
void func::DrawPMD(unsigned int & index)
{
	Union::Get().DrawPMD(index);
}

// PMD�̏���
void func::DeletePMD(unsigned int & index)
{
	Union::Get().DeletePMD(index);
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

// WAVE�̏���
void func::DeleteWAVE(unsigned int & index)
{
	Union::Get().DeleteWAVE(index);
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

// �w�肵���f�B���N�g���̃t�@�C�����擾
std::vector<std::wstring> func::GetDirFile(const std::wstring & path)
{
	return Union::Get().GetDirFile(path);
}

// ���O�C�����[�U�[�l�[���擾
std::wstring func::GetName(void)
{
	std::wstring name;
	DWORD size = 0;

	GetUserName(&name[0], &size);

	name.resize(size);
	GetUserName(&name[0], &size);

	return name;
}
