#pragma once
#include "Actor.h"
#include<vector>
#include"glm/glm.hpp"
using namespace std;
using namespace glm;

//�����ɏo������_�̐��̍ő�l
#define MAX_GENERATE_EXPLOSION_POINTS 20

class Explosion :public Actor
{
private:
	//�e�Ɣ����̈ʒu
	vec2 _pos;
	//�e�Ɣ����̑���
	vec2 _speed;
	//�e�Ɣ����̏��ł���܂ł̃J�E���g
	float _removeCount;
public:
	//�R���X�g���N�^
	Explosion();

	//�X�V����֐�
	void Update() override;
	static void AllUpdate();
	//�`�悷��֐�
	void Draw() override;
	static void AllDraw();
	//�����𔭐�������֐�
	static void GenerateExplosion(vec2 const& pos, int count, float power);
	//�ʒu�̃Q�b�^�ƃZ�b�^
	vec2& GetPosition() { return _pos; }
	void SetPosition(vec2& pos) { _pos = pos; }

	//�����̃Q�b�^�ƃZ�b�^
	vec2& GetSpeed() { return _speed; }
	void SetSpeed(vec2& speed) { _speed = speed; }

	//�J�E���g�̃Q�b�^�ƃZ�b�^
	float GetRemoveCount()const { return _removeCount; }
	void SetRemoveCount(float count) { _removeCount = count; }
};//class Explosion :public Actor


//Explosion�̃f�[�^���Ǘ�����z��
extern vector<Explosion> gExplosions;