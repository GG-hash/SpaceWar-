#pragma once
#include "Actor.h"
#include"glm/glm.hpp"
using namespace glm;

class AI : public Actor
{
private:
	//敵の位置
	vec2 _enemyPos;
	//Shipのインデックス
	int _shipIndex;
	//プレイヤーの方向
	float _toShipAngle;
	//敵の方向
	float _toEnemyAngle;
	//敵への相対角度
	float _toRelativeEnemyAngle;
	//太陽からの角度
	float _fromSunAngle;
	//太陽への角度
	float _toSunAngle;

public:
	//コンストラクタ
	AI();
	//初期化
	int Initialize(int shipIndex);
	//更新する関数
	void Update() override;
	//描画する関数
	void Draw() override;
	//敵の位置のゲッタ
	vec2& GetEnemyPosition() { return _enemyPos; }
};//class AI : public Actor


