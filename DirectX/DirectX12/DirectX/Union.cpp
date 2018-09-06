#define _ENABLE_EXTENDED_ALIGNED_STORAGE
#include "Union.h"
#include "../Window/Window.h"
#include "../Sound/Xaudio2.h"
#include "../Sound/MIDI_IN.h"
#include "../Input/Input.h"
#ifdef _DEBUG
#include "Debug.h"
#endif
#include "Device.h"
#include "Command/Queue.h"
#include "Command/List.h"
#include "Swap.h"
#include "Descriptor/Render.h"
#include "Descriptor/Depth.h"
#include "Fence.h"
#include "Root.h"
#include "Compiler/Compiler.h"
#include "PipeLine/Pipe.h"
#include "Descriptor/Constant.h"
#include "Draw/Point.h"
#include "Draw/Line.h"
#include "Draw/Box.h"
#include "Texture/Texture.h"
#include "PMD/PMD.h"
#include <tchar.h>

#pragma comment(lib, "d3d12.lib")

// �R���X�g���N�^
Union::Union() : 
	alpha(1.0f)
{
	msg = {};
	viewPort = {};
	scissor = {};
	barrier = {};
}

// �f�X�g���N�^
Union::~Union()
{
}

// �E�B���h�E�̃T�C�Y�Z�b�g
void Union::ChangeWindowSize(UINT x, UINT y)
{
	this->x = x;
	this->y = y;
}

// �N���X�̃C���X�^���X��
void Union::Create(void)
{
	win   = std::make_shared<Window> (x, y);
	audio = std::make_shared<Xaudio2>();
	in    = std::make_shared<MIDI_IN>();
	input = std::make_shared<Input>  (win);
#ifdef _DEBUG
	debug = std::make_shared<Debug>();
#endif
	dev    = std::make_shared<Device>();
	queue  = std::make_shared<Queue> (dev);
	list   = std::make_shared<List>  (dev);
	swap   = std::make_shared<Swap>  (win, queue);
	render = std::make_shared<Render>(dev, list, swap);
	depth  = std::make_shared<Depth> (win, dev,  list, swap);
	fence  = std::make_shared<Fence> (dev, queue);
	//���[�g�V�O�l�`������
	CreateRoot();
	com    = std::make_shared<Compiler>();
	//�p�C�v���C������
	CreatePipeLine();

	constant = std::make_shared<Constant>(win, dev,  list);
	point    = std::make_shared<Point>   (win, dev,  list,      pointRoot, pointPipe, constant);
	line     = std::make_shared<Line>    (dev, list, pointRoot, linePipe,  constant);
	box      = std::make_shared<Box>     (dev, list, pointRoot, boxPipe,   constant);
	tex      = std::make_shared<Texture> (dev, list, texRoot,   texPipe,   constant);
	pmd      = std::make_shared<PMD>     (dev, list, modelRoot, modelPipe, constant,  tex);

	ViewPort();
	Scissor();
}

// ���[�g�V�O�l�`���̐���
void Union::CreateRoot(void)
{
	pointRoot = std::make_shared<Root>(dev);
	{
		//�f�B�X�N���v�^�����W�ݒ�p�\����
		D3D12_DESCRIPTOR_RANGE range[] = {
			{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
		};
		//�p�����[�^�ݒ�p�\����
		D3D12_ROOT_PARAMETER param[] = {
			{ D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { 1, &range[0] }, D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_VERTEX },
		};

		pointRoot->CreateRoot(param, _countof(param));
	}

	texRoot = std::make_shared<Root>(dev);
	{
		//�f�B�X�N���v�^�����W�ݒ�p�\����
		D3D12_DESCRIPTOR_RANGE range[] = {
			{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
			{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
		};
		//�p�����[�^�ݒ�p�\����
		D3D12_ROOT_PARAMETER param[] = {
			{ D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { 1, &range[0] }, D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_VERTEX },
			{ D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { 1, &range[1] }, D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL },
		};

		texRoot->CreateRoot(param, _countof(param));
	}

	modelRoot = std::make_shared<Root>(dev);
	{
		//�f�B�X�N���v�^�����W�ݒ�p�\����
		D3D12_DESCRIPTOR_RANGE range[] = {
			{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
			{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
			{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
		};
		//�p�����[�^�ݒ�p�\����
		D3D12_ROOT_PARAMETER param[] = {
			{ D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { 1, &range[0] }, D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_VERTEX },
			{ D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { 1, &range[1] }, D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL },
			{ D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { 1, &range[2] }, D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL },
		};

		modelRoot->CreateRoot(param, _countof(param));
	}
}

// �p�C�v���C���̐���
void Union::CreatePipeLine(void)
{
	pointPipe = std::make_shared<Pipe>(L"Shader/PointShader.hlsl", dev, swap, pointRoot, com);
	linePipe  = std::make_shared<Pipe>(L"Shader/PointShader.hlsl", dev, swap, pointRoot, com);
	boxPipe   = std::make_shared<Pipe>(L"Shader/PointShader.hlsl", dev, swap, pointRoot, com);
	{
		D3D12_INPUT_ELEMENT_DESC input[] =
		{
			{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		pointPipe->CreatePipe(input, _countof(input), D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT);
		linePipe->CreatePipe( input, _countof(input), D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);
		boxPipe->CreatePipe(  input, _countof(input), D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	}

	texPipe = std::make_shared<Pipe>(L"Shader/BasicShader.hlsl", dev, swap, texRoot, com);
	{
		D3D12_INPUT_ELEMENT_DESC input[] =
		{
			{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "ALPHA",    0, DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,       0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		texPipe->CreatePipe(input, _countof(input), D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	}

	modelPipe = std::make_shared <Pipe>(L"Shader/ModelShader.hlsl", dev, swap, modelRoot, com);
	{
		D3D12_INPUT_ELEMENT_DESC input[] =
		{
			{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,       0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		modelPipe->CreatePipe(input, _countof(input), D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	}
}

// �r���[�|�[�g�̃Z�b�g
void Union::ViewPort(void)
{
	viewPort.Height   = static_cast<FLOAT>(y);
	viewPort.MaxDepth = 1.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width    = static_cast<FLOAT>(x);
}

// �V�U�[�̃Z�b�g
void Union::Scissor(void)
{
	scissor.bottom = static_cast<LONG>(y);
	scissor.left   = 0;
	scissor.right  = static_cast<LONG>(x);
	scissor.top    = 0;
}

// �o���A�̃Z�b�g
void Union::Barrier(D3D12_RESOURCE_STATES befor, D3D12_RESOURCE_STATES affter)
{
	barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE::D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource   = render->GetResource(swap->Get()->GetCurrentBackBufferIndex());
	barrier.Transition.StateBefore = befor;
	barrier.Transition.StateAfter  = affter;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;

	//�o���A�ݒu
	list->GetList()->ResourceBarrier(1, &barrier);
}

// ���b�Z�[�W�̊m�F
bool Union::CheckMsg(void)
{
	if (msg.message == WM_QUIT)
	{
		return false;
	}
	else
	{
		//�Ăяo�����X���b�h�����L���Ă���E�B���h�E�ɑ��M���ꂽ���b�Z�[�W�ۗ̕�����Ă��镨���擾
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
			TranslateMessage(&msg);
			//1�̃E�B�h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o����
			DispatchMessage(&msg);
		}
	}

	return true;
}

// �r���[�s��̃Z�b�g
void Union::ChangeView(const Vec3f & pos, const Vec3f & target, const Vec3f & up)
{
	constant->ChangeView(pos, target, up);
}

// �`�揀��
void Union::Set(void)
{
	list->Reset(nullptr);

	/*list->SetRoot(pointRoot->Get());

	list->SetPipe(pointPipe->Get());*/

	constant->UpDataWVP();

	list->SetViewPort(viewPort);

	list->SetScissor(scissor);

	Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET);

	render->SetRender(depth->GetHeap());

	depth->SetDepth();
}

// ���s
void Union::Do(void)
{
	point->Draw();
	line->Draw();
	box->Draw();

	Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT);

	list->Close();

	//�R�}���h���s.
	ID3D12CommandList* ppCmdLists[] = {
		list->GetList(),
	};
	queue->Get()->ExecuteCommandLists(_countof(ppCmdLists), ppCmdLists);

	swap->Present();

	fence->Wait();

	point->Reset();
	line->Reset();
	box->Reset();
}

// �L�[����
bool Union::CheckKey(UINT index)
{
	return input->CheckKey(index);
}

// �g���K�[�L�[����
bool Union::TriggerKey(UINT index)
{
	return input->TriggerKey(index);
}

// �_�̕`��
void Union::DrawPoint(const Vec2f & pos, const Vec3f & color)
{
	point->AddList(pos, color, alpha);
}

// ���C���̕`��
void Union::DrawLine(const Vec2f & pos1, const Vec2f & pos2, const Vec3f & color)
{
	line->AddList(pos1, pos2, color, alpha);
}

// �{�b�N�X�̕`��
void Union::DrawBox(const Vec2f & pos, const Vec2f & size, const Vec3f & color)
{
	box->AddList(pos, size, color, alpha);
}

// �摜�ǂݍ���
void Union::LoadImg(UINT & index, const std::string & fileName)
{
	tex->LoadWIC(index, fileName);
}

// �`��
void Union::Draw(UINT& index, const Vec2f& pos, UINT turnX, UINT turnY)
{
	tex->Draw(index, pos, alpha, turnX, turnY);
}

// �`��E�T�C�Y�w��
void Union::Draw(UINT & index, const Vec2f & pos, const Vec2f & size, UINT turnX, UINT turnY)
{
	tex->Draw(index, pos, size, alpha, turnX, turnY);
}

// �`��E�T�C�Y�w��E����
void Union::Draw(UINT& index, const Vec2f& pos, const Vec2f& size, const Vec2f& rect, const Vec2f& rectSize, UINT turnX, UINT turnY)
{
	tex->Draw(index, pos, size, rect, rectSize, alpha, turnX, turnY);
}

// �摜�̏���
void Union::DeleteImg(UINT & index)
{
	tex->Delete(index);
}

// PMD�ǂݍ���
void Union::LoadPMD(UINT & index, const std::string & fileName)
{
	pmd->LoadPMD(index, fileName);
}

// PMD�`��
void Union::DrawPMD(UINT & index)
{
	pmd->Draw(index);
}

// PMD�̏���
void Union::DeletePMD(UINT & index)
{
	pmd->Delete(index);
}

// WAVE�ǂݍ���
void Union::LoadWave(UINT& index, const std::string & fileName)
{
	audio->LoadWAVE(index, fileName);
}

// WAVE�̍Đ�
void Union::PlayWave(UINT& index)
{
	audio->Play(index);
}

// WAVE�̍Đ���~
void Union::StopWave(UINT& index)
{
	audio->Stop(index);
}

// WAVE�̏���
void Union::DeleteWAVE(UINT & index)
{
	audio->Delete(index);
}

// MIDI�f�o�C�X���̎擾
UINT Union::GetMidiNum(void)
{
	return in->GetDevNum();
}

// MIDI�X�e�[�^�X�o�C�g�̎擾
UCHAR Union::GetMidiState(void)
{
	return in->GetState();
}

// MIDI�f�[�^�o�C�g1�̎擾
UCHAR Union::GetMidiData1(void)
{
	return in->GetData1();
}

// MIDI�f�[�^�o�C�g2�̎擾
UCHAR Union::GetMidiData2(void)
{
	return in->GetData2();
}

// �t�@�C����Ԃ�
std::string Union::GetFile(const fs::path & p)
{
	std::string m;
	//�t�@�C���̏ꍇ
	if (fs::is_regular_file(p))
	{
		m = p.filename().string();
	}
	else if (fs::is_directory(p))
	{
		//m = p.string();
	}

	return m;
}

// �t�@�C����Ԃ�
std::wstring Union::GetFileW(const fs::path & p)
{
	std::wstring m;
	//�t�@�C���̏ꍇ
	if (fs::is_regular_file(p))
	{
		m = p.filename().wstring();
	}
	else if (fs::is_directory(p))
	{
		//m = p.wstring();
	}

	return m;
}

// �f�B���N�g���̃t�@�C����
std::vector<std::string> Union::GetDirFile(const std::string & point)
{
	//�񋓂̋N�_
	fs::path p(point.c_str());

	std::vector<std::string>fileName;

	for (auto& i : fs::recursive_directory_iterator(p))
	{
		auto dummy = GetFile(i);
		if (dummy.size() > 0)
		{
			fileName.push_back(dummy);
		}
	}

	return fileName;
}

// �f�B���N�g���̃t�@�C����
std::vector<std::wstring> Union::GetDirFile(const std::wstring & point)
{
	//�񋓂̋N�_
	fs::path p(point.c_str());

	std::vector<std::wstring>fileName;

	for (auto& i : fs::recursive_directory_iterator(p))
	{
		auto dummy = GetFileW(i);
		if (dummy.size() > 0)
		{
			fileName.push_back(dummy);
		}
	}

	return fileName;
}