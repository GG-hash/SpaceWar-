#pragma once
#include"Explosion.h"

//�e�̃X�s�[�h
#define BULLET_SPEED 1.5f
//�e�����ł���܂ł̎���
#define MAX_BULLET_COUNT (60*2)

//�e�̈ʒu��\�����ԂȂǂ͔����̃G�t�F�N�g�Ƌ��ʂ���ӏ�����������
//Explosion�N���X�Œe�̏������قƂ�Ǎs��
class Bullet : public Explosion
{
private:

public:
	//�R���X�g���N�^
	Bullet() {};
	//�X�V����֐�
	void Update() override;
	//�`�悷��֐�
	//void Draw() override;



};//class ShipBullet : public Actor


