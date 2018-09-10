#pragma once
#include "../Descriptor.h"
#include "../../etc/Typedef.h"
#include "../../etc/Vector3.h"
#include <vector>

class Window;
/*
*/

class Constant :
	public Descriptor
{
public:
	// �R���X�g���N�^
	Constant(std::weak_ptr<Window>win, std::weak_ptr<Device>dev, std::weak_ptr<List>list);
	// �f�X�g���N�^
	~Constant();

	// WVP�̕ύX
	void ChangeView(const Vec3f& pos, const Vec3f& target, const Vec3f& up);

	// WVP�̍X�V
	void UpDataWVP(void);

	// �萔�o�b�t�@�̃Z�b�g
	void SetConstant(UINT rootIndex = 0, UINT index = 0);

	// ���\�[�X�̎擾
	ID3D12Resource* GetResoure(UINT index) const {
		return resource[index];
	}
	// ���\�[�X�̎擾
	std::vector<ID3D12Resource*> GetResoure() const {
		return resource;
	}
	
private:
	// WVP�̃Z�b�g
	void SetWVP(void);

	// ���\�[�X�̐���
	HRESULT CreateResource(UINT index, UINT64 size);

	// ���\�[�X�r���[�̐���
	HRESULT CreateView(UINT index, UINT size);

	// ����
	void Create(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// ���\�[�X
	std::vector<ID3D12Resource*> resource;

	// ���M�f�[�^
	std::vector<UINT8*> data;

	// WVP
	WVP wvp;
};
