#pragma once
#include "Actor.h"

//�f���̏����Ɋւ���N���X
//�f���͉�ʂ̒��S�ɂ���A���͂������Ă���
//�������Ă��܂��ƃ~�X�ƂȂ�
//�f���̈ʒu�͌��_(��ʂ̒��S�ł���)
class Planet :public Actor
{
private:

public:
	//�X�V����֐�
	void Update() override;
	//�`��֐�
	void Draw() override;
};//class Planet :public Actor

//�O���[�o���ȃC���X�^���X
extern Planet gPlanet;
