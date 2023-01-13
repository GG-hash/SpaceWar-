#pragma once
#include"Explosion.h"

//弾のスピード
#define BULLET_SPEED 1.5f
//弾が消滅するまでの時間
#define MAX_BULLET_COUNT (60*2)

//弾の位置や表示時間などは爆発のエフェクトと共通する箇所が多いため
//Explosionクラスで弾の処理をほとんど行う
class Bullet : public Explosion
{
private:

public:
	//コンストラクタ
	Bullet() {};
	//更新する関数
	void Update() override;
	//描画する関数
	//void Draw() override;



};//class ShipBullet : public Actor


