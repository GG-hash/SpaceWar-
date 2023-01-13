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
	//Shipからのキーの入力
	Ship& ship = gShips[_shipIndex];
	Ship& enemy = gShips[_shipIndex ^ 1];
	bool* keys = ship._keys;
	bool* lastKeys = ship._lastKeys;

	//デモ画面用にキーのデータをセットする
	//キーをクリアする
	memset(keys, 0, sizeof(keys));

	//敵の向きを求める
	//敵へのベクトルを求める
	vec2 tmpEnemyPos = enemy.GetPosition() - ship.GetPosition();
	_toEnemyAngle = -atan2(tmpEnemyPos.x, tmpEnemyPos.y);
	//太陽への角度
	_toSunAngle = FixRadianAngle(-atan2(ship.GetPosition().x, ship.GetPosition().y) + (float)M_PI);

	//太陽からの角度を求める
	_fromSunAngle = -atan2(ship.GetPosition().x, ship.GetPosition().y);
	//太陽は円なので、円の接線方向に向きを変えることで太陽を避ける
	float avoidSunRotate = _fromSunAngle + (float)M_PI / 2.0f;

	//攻撃するか判定するフラグ
	bool attack = false;

	//自分自身から太陽への角度と敵への角度が1rad (ほぼ対角線)なら
	//太陽を避ける
	if ((enemy._isDead == false) && (fabs(_toSunAngle - _toEnemyAngle) < 0.5f))
	{
		//太陽を避けるように進む
		float screenRadius = (float)SCREEN_HEIGHT / 2.0f;
		//スクリーンの高さの半径の70%離れた位置で旋回する
		_enemyPos = vec2(-sin(avoidSunRotate), cos(avoidSunRotate)) * screenRadius * 0.7f;
	}//if (fabs(_toSunAngle - _toEnemyAngle) < 0.5f)
	//対角線上に太陽が無ければ敵へ向かう
	else
	{
		//敵が倒されていなければ攻撃
		if (enemy._isDead == false)
		{
			//攻撃開始
			attack = true;
			_enemyPos = enemy.GetPosition();
		}

	}//else

	//敵への方向を求める
	vec2 toEnemyDistance = _enemyPos - ship.GetPosition();
	_toShipAngle = -atan2(toEnemyDistance.x, toEnemyDistance.y);
	//敵の相対的な方向を求める
	_toRelativeEnemyAngle = _toShipAngle - ship.GetRotate();
	//回転の範囲を -M_PI < _rotate < M_PI とする
	_toRelativeEnemyAngle = FixRadianAngle(_toRelativeEnemyAngle);

	//敵機が自機から見て右の位置にいる時の処理
	if (_toRelativeEnemyAngle < 0.0f)
	{
		keys[SHIP_KEY_RIGHT] = true;
	}//if (_toRelativeEnemyAngle < 0.0f)
	//敵機が自機から見て左の位置にいる時の処理
	else if (_toRelativeEnemyAngle > 0.0f)
	{
		keys[SHIP_KEY_LEFT] = true;
	}//else if (_toRelativeEnemyAngle > 0.0f)

	//敵の相対位置と自分の向いている方向がほぼ一致したら、
	//加速して敵の方へ向かう
	if (fabs(FixRadianAngle(_toShipAngle - ship.GetRotate())) < 0.5f)
	{
		keys[SHIP_KEY_ACCEL] = true;
	}//if (fabs(FixRadianAngle(_toRelativeEnemyAngle - ship.GetRotate())) < 0.5f)

	if ((attack == true) &&                            //attackのフラグがtrue
		(fabs(_toRelativeEnemyAngle) < 0.5f) &&        //敵機の方向に向いている
		(length(tmpEnemyPos) < SCREEN_WIDTH / 2.0f) &&  //敵との距離がスクリーンの幅の1/2
		(lastKeys[SHIP_KEY_ATTACK] == false) &&       //1フレーム前に弾を撃っていない
		(rand() % 4 == 0))                           //余りにも早い連続射撃を防ぐ
	{
		keys[SHIP_KEY_ATTACK] = true;
	}//if (lastKeys[SHIP_KEY_ATTACK] == true)


}//void AI::Update()

void AI::Draw()
{
}//void AI::Draw()



