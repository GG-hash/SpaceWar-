#pragma once
#include "Actor.h"

//���z�̏����Ɋւ���N���X
//���z�͉�ʂ̒��S�ɂ���A���͂������Ă���
//�������Ă��܂��ƃ~�X�ƂȂ�
//���z�̈ʒu�͌��_(��ʂ̒��S�ł���)
class Sun :public Actor
{
private:

public:
	//�X�V����֐�
	void Update() override;
	//�`��֐�
	void Draw() override;
};//class Sun :public Actor

//�O���[�o���ȃC���X�^���X
extern Sun gSun;
