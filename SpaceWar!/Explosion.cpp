#define _USE_MATH_DEFINES
#include<cmath>
#include "Explosion.h"
#include"GameHeader.h"
#include"glut.h"
#include"Bullet.h"

//Explosionのデータを管理する配列
vector<Explosion> gExplosions;

Explosion::Explosion() :_pos(vec2(0, 0))
, _speed(vec2(0, 0))
, _removeCount(0)
{
}//Explosion::Explosion()

void Explosion::Update()
{
	//位置を更新する
	_pos += _speed;

	//弾が画面外に出たら弾を画面反対へワープする
	if (_pos.x < -SCREEN_WIDTH / 2.0f)
	{
		_pos.x += SCREEN_WIDTH;
	}
	if (_pos.x >= SCREEN_WIDTH / 2.0f)
	{
		_pos.x -= SCREEN_WIDTH;
	}
	if (_pos.y < -SCREEN_HEIGHT / 2.0f)
	{
		_pos.y += SCREEN_HEIGHT;
	}
	if (_pos.y >= SCREEN_HEIGHT / 2.0f)
	{
		_pos.y -= SCREEN_HEIGHT;
	}

	//カウントを減らす
	if (_removeCount > 0)
	{
		_removeCount--;
	}
}//void Explosion::Update()


void Explosion::Draw()
{
}
//void Explosion::Draw()

void Explosion::AllDraw()
{
	//配列にデータが無ければ処理を飛ばす
	if (gExplosions.size() <= 0)
	{
		return;
	}
	vec2& position = gExplosions.data()->GetPosition();

	glVertexPointer(2, GL_FLOAT, sizeof(Explosion), &position);
	glDrawArrays(GL_POINTS, 0, gExplosions.size());
}
//void Explosion::AllDraw()

void Explosion::GenerateExplosion(vec2 const& pos, int count, float power)
{
	for (int i = 0; i < count; i++)
	{
		Explosion explosion = {};
		explosion._pos = pos;
		//速さのセット
		//爆発のエフェクトを生成する
		{
			float rotate = (float)M_PI * 2.0f * (float)rand() / RAND_MAX;
			float pow = power * (float)rand() / RAND_MAX;
			explosion._speed = vec2(-sin(rotate), cos(rotate)) * pow;
		}
		//爆発の表示時間のセット
		explosion._removeCount = 60.0f * (float)rand() / RAND_MAX;
		//データを最後尾に追加する
		gExplosions.push_back(explosion);
	}//for (int i = 0; i < MAX_GENERATE_EXPLOSION_POINTS; i++)

}//void Explosion::GenerateExplosion(vec2 const& pos, int count, float power)




void Explosion::AllUpdate()
{
	//配列にデータが無ければ処理を飛ばす
	if (gExplosions.size() <= 0)
	{
		return;
	}

	for (auto explosion = gExplosions.begin();
		explosion != gExplosions.end();)
	{
		(*explosion).Update();

		//表示時間が0ならエフェクトを削除する
		if ((*explosion).GetRemoveCount() <= 0)
		{
			explosion = gExplosions.erase(explosion);

		}//if ((*explosion).GetRemoveCount() <= 0)
		else
		{
			explosion++;
		}


	}//for (auto explosion = gExplosions.begin(); explosion != gExplosions.end();)
}//void Explosion::AllUpdate()


