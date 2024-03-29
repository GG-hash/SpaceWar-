#pragma once
#include "Actor.h"
#include"glm/glm.hpp"
using namespace glm;

class AI : public Actor
{
private:
	//ターゲットの位置
	vec2 _targetPos;
	//Shipのインデックス
	int _shipIndex;
	//プレイヤーの方向
	float _toShipAngle;
	//敵の方向
	float _toEnemyAngle;
	//敵への相対角度
	float _toRelativeEnemyAngle;
	//惑星からの角度
	float _fromPlanetAngle;
	//惑星への角度
	float _toPlanetAngle;

public:
	//コンストラクタ
	AI();
	//初期化
	int Initialize(int shipIndex);
	//更新する関数
	void Update() override;
	//描画する関数
	void Draw() override;
	//ターゲットの位置のゲッタ
	vec2& GetTargetPosition() { return _targetPos; }
};//class AI : public Actor


