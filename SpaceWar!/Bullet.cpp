#include "Bullet.h"

//Bullet::Bullet():_pos(vec2(0,0))
//				,_speed(vec2(0,0))
//				,_removeCount(0)
//{
//}

void Bullet::Update()
{
	//����������������ȉ��̏���������
	if (GetRemoveCount() > 0)
	{
		//�e�̈ʒu�̍X�V
		Explosion::Update();
		//�e�̕\�����Ԃ��I��������̏���
		if (GetRemoveCount() <= 0)
		{
			Explosion::GenerateExplosion(GetPosition(), MAX_GENERATE_EXPLOSION_POINTS, 0.1f);
		}
	}//if (GetRemoveCount() > 0)




}//void ShipBullet::Update()


//void Bullet::Draw()
//{
//}//void ShipBullet::Draw()

