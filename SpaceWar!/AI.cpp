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
	//�U�����邩���肷��t���O
	bool attack = false;
	
	//�L�[���N���A����
	memset(keys, 0, sizeof(keys));

	//�G�̌��������߂�
	//���g�̑D����G�ւ̃x�N�g�������߂�
	vec2 toEnemyPosVec = enemy.GetPosition() - ship.GetPosition();
	_toEnemyAngle = -atan2(toEnemyPosVec.x, toEnemyPosVec.y);

	//printf("_toEnemyAngle : %f\n", _toEnemyAngle * 180.0f/M_PI);
	//printf("atan2 Angle   : %f\n", atan2(toEnemyPosVec.y, toEnemyPosVec.x));

	//�f���ւ̊p�x�A�܂�f������̊p�x�Ɛ^���΂ƂȂ�
	_toPlanetAngle = FixRadianAngle(_fromPlanetAngle + (float)M_PI);
	//�f���̈ʒu
	vec2 planetPos = vec2(0.0f, 0.0f);
	//�f������Ƃ����f������̊p�x�����߂�
	_fromPlanetAngle = -atan2(ship.GetPosition().x - planetPos.x, ship.GetPosition().y - planetPos.y);
	//�����̌����Ă����������90��������������ڕW�ɂ���B
	float avoidPlanetRotate = _fromPlanetAngle + (float)M_PI / 2.0f;
	


	//�������g����f���ւ̊p�x�ƓG�ւ̊p�x��0.5rad (�قڑΊp��)�Ȃ�
	//�f���������
	if ((enemy._isDead == false) && (fabs(_toPlanetAngle - _toEnemyAngle) < 0.5f))
	{

		//�f���������悤�ɐi��
		float distance = sqrtf(powf(ship.GetPosition().x - planetPos.x,2.0f) + powf(ship.GetPosition().y - planetPos.y,2.0f));
		//�ɍ��W���璼�����W�����߁A�f���𒆐S�Ƃ���90����̈ʒu�����߂�
		_targetPos = vec2(-sin(avoidPlanetRotate), cos(avoidPlanetRotate)) * distance;


		//�X�N���[���̍����̔��a��70%���ꂽ�ʒu�Ő��񂷂�
		//float screenRadius = (float)SCREEN_HEIGHT / 2.0f;
		//_enemyPos = vec2(-sin(avoidPlanetRotate), cos(avoidPlanetRotate)) * screenRadius * 0.7f;
		
	}//if (fabs(_toPlanetAngle - _toEnemyAngle) < 0.5f)
	//�Ίp����ɘf����������ΓG�֌�����
	else
	{
		//�G���|����Ă��Ȃ���΍U��
		if (enemy._isDead == false)
		{
			//�U���J�n
			attack = true;
			_targetPos = enemy.GetPosition();
		}

	}//else

	//�ړI�Ƃ�����������߂�
	vec2 toTarget = _targetPos - ship.GetPosition();
	_toShipAngle = -atan2(toTarget.x, toTarget.y);

	
	//�v���C���[�̌����Ă����������Ƃ����A�G�̑��ΓI�ȕ��������߂�
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


	//State Accel
	//�G�̑��Έʒu�Ǝ����̌����Ă���������قڈ�v������A
	//�������ēG�̕��֌�����
	if (fabs(FixRadianAngle(_toShipAngle - ship.GetRotate())) < 0.5f)
	{
		keys[SHIP_KEY_ACCEL] = true;
	}//if (fabs(FixRadianAngle(_toRelativeEnemyAngle - ship.GetRotate())) < 0.5f)

	//State Attack
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



