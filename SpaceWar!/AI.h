#pragma once
#include "Actor.h"
#include"glm/glm.hpp"
using namespace glm;

class AI : public Actor
{
private:
	//�^�[�Q�b�g�̈ʒu
	vec2 _targetPos;
	//Ship�̃C���f�b�N�X
	int _shipIndex;
	//�v���C���[�̕���
	float _toShipAngle;
	//�G�̕���
	float _toEnemyAngle;
	//�G�ւ̑��Ίp�x
	float _toRelativeEnemyAngle;
	//�f������̊p�x
	float _fromPlanetAngle;
	//�f���ւ̊p�x
	float _toPlanetAngle;

public:
	//�R���X�g���N�^
	AI();
	//������
	int Initialize(int shipIndex);
	//�X�V����֐�
	void Update() override;
	//�`�悷��֐�
	void Draw() override;
	//�^�[�Q�b�g�̈ʒu�̃Q�b�^
	vec2& GetTargetPosition() { return _targetPos; }
};//class AI : public Actor


