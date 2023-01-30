#include "AI.h"
#include"Ship.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Math.h"

AI::AI() :_shipIndex(0)
{
}//AI::AI()

int AI::Initialize(int shipIndex)
{
	_shipIndex = shipIndex;
	return 0;
}//int AI::Initialize(int shipIndex)

void AI::Update()
{
	//Ship����̃L�[�̓���
	Ship& ship = gShips[_shipIndex];
	Ship& enemy = gShips[(_shipIndex + 1) % 2];
	bool* keys = ship._keys;
	bool* lastKeys = ship._lastKeys;

	//�L�[���N���A����
	memset(keys, 0, sizeof(keys));

	//�G�̌��������߂�
	//���g�̑D����G�ւ̃x�N�g�������߂�
	vec2 toEnemyPosVec = enemy.GetPosition() - ship.GetPosition();
	_toEnemyAngle = -atan2(toEnemyPosVec.x, toEnemyPosVec.y);

	//�f������̊p�x�����߂�
	vec2 planetPos = vec2(0.0f, 0.0f);
	//�D�̐�[�Ƙf���̊p�x�����߂�
	_fromPlanetAngle = -atan2(ship.GetPosition().x - planetPos.x, ship.GetPosition().y - planetPos.y);
	//�f���ւ̊p�x�A�܂�f������̊p�x�Ɛ^���΂ƂȂ�
	_toPlanetAngle = FixRadianAngle(_fromPlanetAngle + (float)M_PI);

	//�f���͉~�Ȃ̂ŁA�~�̐ڐ������Ɍ�����ς��邱�ƂŘf���������
	float avoidPlanetRotate = _fromPlanetAngle + (float)M_PI / 2.0f;

	//�U�����邩���肷��t���O
	bool attack = false;

	//�������g����f���ւ̊p�x�ƓG�ւ̊p�x��0.5rad (�قڑΊp��)�Ȃ�
	//�f���������
	if ((enemy._isDead == false) && (fabs(_toPlanetAngle - _toEnemyAngle) < 0.5f))
	{
		//�f���������悤�ɐi��
		float screenRadius = (float)SCREEN_HEIGHT / 2.0f;
		//�X�N���[���̍����̔��a��70%���ꂽ�ʒu�Ő��񂷂�
		//�ɍ��W���璼�����W�����߂�
		//����ɂ��A�p�x�̏�񂾂��ňړ��ł���
		_enemyPos = vec2(-sin(avoidPlanetRotate), cos(avoidPlanetRotate)) * screenRadius * 0.7f;
	}//if (fabs(_toPlanetAngle - _toEnemyAngle) < 0.5f)
	//�Ίp����ɘf����������ΓG�֌�����
	else
	{
		//�G���|����Ă��Ȃ���΍U��
		if (enemy._isDead == false)
		{
			//�U���J�n
			attack = true;
			_enemyPos = enemy.GetPosition();
		}

	}//else

	//�G�ւ̕��������߂�
	vec2 toEnemyNewPosVec = _enemyPos - ship.GetPosition();
	_toShipAngle = -atan2(toEnemyNewPosVec.x, toEnemyNewPosVec.y);
	//�G�̑��ΓI�ȕ��������߂�
	_toRelativeEnemyAngle = _toShipAngle - ship.GetRotate();
	//��]�͈̔͂� -M_PI < _rotate < M_PI �Ƃ���
	_toRelativeEnemyAngle = FixRadianAngle(_toRelativeEnemyAngle);

	//�G�@�����@���猩�ĉE�̈ʒu�ɂ��鎞�̏���
	if (_toRelativeEnemyAngle < 0.0f)
	{
		keys[SHIP_KEY_RIGHT] = true;
	}//if (_toRelativeEnemyAngle < 0.0f)
	//�G�@�����@���猩�č��̈ʒu�ɂ��鎞�̏���
	else if (_toRelativeEnemyAngle > 0.0f)
	{
		keys[SHIP_KEY_LEFT] = true;
	}//else if (_toRelativeEnemyAngle > 0.0f)

	//�G�̑��Έʒu�Ǝ����̌����Ă���������قڈ�v������A
	//�������ēG�̕��֌�����
	if (fabs(FixRadianAngle(_toShipAngle - ship.GetRotate())) < 0.5f)
	{
		keys[SHIP_KEY_ACCEL] = true;
	}//if (fabs(FixRadianAngle(_toRelativeEnemyAngle - ship.GetRotate())) < 0.5f)

	if ((attack == true) &&                            //attack�̃t���O��true
		(fabs(_toRelativeEnemyAngle) < 0.5f) &&        //�G�@�̕����Ɍ����Ă���
		(length(toEnemyPosVec) < SCREEN_WIDTH / 2.0f) &&  //�G�Ƃ̋������X�N���[���̕���1/2
		(lastKeys[SHIP_KEY_ATTACK] == false) &&       //1�t���[���O�ɒe�������Ă��Ȃ�
		(rand() % 4 == 0))                           //�]��ɂ������A���ˌ���h��
	{
		keys[SHIP_KEY_ATTACK] = true;
	}//if (lastKeys[SHIP_KEY_ATTACK] == true)


}//void AI::Update()

void AI::Draw()
{
}//void AI::Draw()



