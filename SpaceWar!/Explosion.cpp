#define _USE_MATH_DEFINES
#include<cmath>
#include "Explosion.h"
#include"GameHeader.h"
#include"glut.h"
#include"Bullet.h"

//Explosion�̃f�[�^���Ǘ�����z��
vector<Explosion> gExplosions;

Explosion::Explosion() :_pos(vec2(0, 0))
, _speed(vec2(0, 0))
, _removeCount(0)
{
}//Explosion::Explosion()

void Explosion::Update()
{
	//�ʒu���X�V����
	_pos += _speed;

	//�e����ʊO�ɏo����e����ʔ��΂փ��[�v����
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

	//�J�E���g�����炷
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
	//�z��Ƀf�[�^��������Ώ������΂�
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
		//�����̃Z�b�g
		//�����̃G�t�F�N�g�𐶐�����
		{
			float rotate = (float)M_PI * 2.0f * (float)rand() / RAND_MAX;
			float pow = power * (float)rand() / RAND_MAX;
			explosion._speed = vec2(-sin(rotate), cos(rotate)) * pow;
		}
		//�����̕\�����Ԃ̃Z�b�g
		explosion._removeCount = 60.0f * (float)rand() / RAND_MAX;
		//�f�[�^���Ō���ɒǉ�����
		gExplosions.push_back(explosion);
	}//for (int i = 0; i < MAX_GENERATE_EXPLOSION_POINTS; i++)

}//void Explosion::GenerateExplosion(vec2 const& pos, int count, float power)




void Explosion::AllUpdate()
{
	//�z��Ƀf�[�^��������Ώ������΂�
	if (gExplosions.size() <= 0)
	{
		return;
	}

	for (auto explosion = gExplosions.begin();
		explosion != gExplosions.end();)
	{
		(*explosion).Update();

		//�\�����Ԃ�0�Ȃ�G�t�F�N�g���폜����
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


