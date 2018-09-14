#pragma once
#include "../../Source/etc/Vector2.h"

class BaseObj
{
public:
	// �R���X�g���N�^
	BaseObj();
	// �f�X�g���N�^
	virtual ~BaseObj();

	// ���W�̎擾
	Vec2f GetPos(void) const {
		return pos;
	}
	// ���W�̃Z�b�g
	void SetPos(const Vec2f& pos) {
		this->pos = pos;
	}

	// �T�C�Y�̎擾
	Vec2f GetSize(void) const {
		return size;
	}
	// �T�C�Y�̃Z�b�g
	void SetSize(const Vec2f& size) {
		this->size = size;
	}

	// �g�嗦�̎擾
	float GetLarge(void) const {
		return large;
	}
	// �g�嗦�̃Z�b�g
	void SetLarge(float large) {
		this->large = large;
	}

protected:
	// ���W
	Vec2f pos;

	// �T�C�Y
	Vec2f size;

	// �g�嗦
	float large;
};

