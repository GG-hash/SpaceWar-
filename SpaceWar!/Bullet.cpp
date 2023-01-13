#include "Bullet.h"

//Bullet::Bullet():_pos(vec2(0,0))
//				,_speed(vec2(0,0))
//				,_removeCount(0)
//{
//}

void Bullet::Update()
{
	//爆発が発生したら以下の処理をする
	if (GetRemoveCount() > 0)
	{
		//弾の位置の更新
		Explosion::Update();
		//弾の表示時間が終わった時の処理
		if (GetRemoveCount() <= 0)
		{
			Explosion::GenerateExplosion(GetPosition(), MAX_GENERATE_EXPLOSION_POINTS, 0.1f);
		}
	}//if (GetRemoveCount() > 0)




}//void ShipBullet::Update()


//void Bullet::Draw()
//{
//}//void ShipBullet::Draw()

