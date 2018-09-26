#pragma once
#include "../etc/Vector2.h"

class BackGround
{
public:
	// �R���X�g���N�^
	BackGround();
	// �f�X�g���N�^
	~BackGround();

	// �`��
	void Draw(void);

	// ���W�̎擾
	Vec2 GetPos(void) const {
		return pos;
	}
	// ���W�̃Z�b�g
	void SetPos(const Vec2& pos) {
		this->pos = pos;
	}

	// �T�C�Y�̎擾
	Vec2 GetSize(void) const {
		return size;
	}
	// �T�C�Y�̃Z�b�g
	void SetSize(const Vec2& size) {
		this->size = size;
	}

private:
	// �摜
	int image;

	// ���W
	Vec2 pos;

	// �T�C�Y
	Vec2 size;
};

