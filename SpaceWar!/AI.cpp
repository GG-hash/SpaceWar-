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
	Ship& enemy = gShips[_shipIndex ^ 1];
	bool* keys = ship._keys;
	bool* lastKeys = ship._lastKeys;

	//�f����ʗp�ɃL�[�̃f�[�^���Z�b�g����
	//�L�[���N���A����
	memset(keys, 0, sizeof(keys));

	//�G�̌��������߂�
	//�G�ւ̃x�N�g�������߂�
	vec2 tmpEnemyPos = enemy.GetPosition() - ship.GetPosition();
	_toEnemyAngle = -atan2(tmpEnemyPos.x, tmpEnemyPos.y);
	//���z�ւ̊p�x
	_toSunAngle = FixRadianAngle(-atan2(ship.GetPosition().x, ship.GetPosition().y) + (float)M_PI);

	//���z����̊p�x�����߂�
	_fromSunAngle = -atan2(ship.GetPosition().x, ship.GetPosition().y);
	//���z�͉~�Ȃ̂ŁA�~�̐ڐ������Ɍ�����ς��邱�Ƃő��z�������
	float avoidSunRotate = _fromSunAngle + (float)M_PI / 2.0f;

	//�U�����邩���肷��t���O
	bool attack = false;

	//�������g���瑾�z�ւ̊p�x�ƓG�ւ̊p�x��1rad (�قڑΊp��)�Ȃ�
	//���z�������
	if ((enemy._isDead == false) && (fabs(_toSunAngle - _toEnemyAngle) < 0.5f))
	{
		//���z�������悤�ɐi��
		float screenRadius = (float)SCREEN_HEIGHT / 2.0f;
		//�X�N���[���̍����̔��a��70%���ꂽ�ʒu�Ő��񂷂�
		_enemyPos = vec2(-sin(avoidSunRotate), cos(avoidSunRotate)) * screenRadius * 0.7f;
	}//if (fabs(_toSunAngle - _toEnemyAngle) < 0.5f)
	//�Ίp����ɑ��z��������ΓG�֌�����
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
	vec2 toEnemyDistance = _enemyPos - ship.GetPosition();
	_toShipAngle = -atan2(toEnemyDistance.x, toEnemyDistance.y);
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
		(length(tmpEnemyPos) < SCREEN_WIDTH / 2.0f) &&  //�G�Ƃ̋������X�N���[���̕���1/2
		(lastKeys[SHIP_KEY_ATTACK] == false) &&       //1�t���[���O�ɒe�������Ă��Ȃ�
		(rand() % 4 == 0))                           //�]��ɂ������A���ˌ���h��
	{
		keys[SHIP_KEY_ATTACK] = true;
	}//if (lastKeys[SHIP_KEY_ATTACK] == true)


}//void AI::Update()

void AI::Draw()
{
}//void AI::Draw()



