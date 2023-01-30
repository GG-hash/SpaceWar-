#pragma once
#include<cstdio>
#include<vector>
#include<Windows.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"glut.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"Actor.h"
#include"GameHeader.h"
#include"Bullet.h"
#include"AI.h"
using namespace std;
using namespace glm;

//Ship�̍ő�̉����x
#define SHIP_ACCELERATION 0.001f
//Ship�����邱�Ƃ̂ł���ő�̃X�R�A
#define MAX_SHIP_SCORE 3


//Ship�̐����`����
//���O��bmp�t�@�C���ɑΉ�������
enum ShipType
{
	SHIP_INDEX_WEDGE,
	SHIP_INDEX_NEEDLE,
	MAX_INDEX_SHIP //�ő��Ship�̐�
};

//������Ă���L�[�̃^�C�v
enum ShipKey
{
	SHIP_KEY_LEFT,
	SHIP_KEY_RIGHT,
	SHIP_KEY_ACCEL,
	SHIP_KEY_ATTACK,
	MAX_SHIP_KEY
};

class Ship : public Actor
{
private:
	//Ship��`�悷��_�̔z��
	vector<vec2> _points;
	//�ϊ���̒��_�̍��W
	vector<vec2> _transPoints;
	//Ship�̃T�C�Y
	vec2 _size;
	//Ship�̍��W
	vec2 _pos;
	//Ship�̃f�t�H���g���W
	vec2 _defaultPos;
	//Ship�̉�]�̊p�x
	float _rotate;
	//Ship�̃f�t�H���g�̉�]�̊p�x
	float _defaultRotate;
	//Ship�̃X�s�[�h
	vec2 _speed;
	////�����{�^����������Ă��邩�𔻒肷��
	//bool _accel;
	////�����������𔻒肷��
	//bool _lastAccel;

	//�e�̔z��
	vector<Bullet> _bullets;
	//�e�̃J�E���g
	int _bulletCount;
	//�e�̔��ˏ�Ԃ̃t���O
	bool _lastAttack;
	//Ship�̃C���f�b�N�X
	int _index;
	//�ϊ��s��
	mat4 _transMatrix;
	//AI�̃C���X�^���X
	AI _ai;
	//�X�R�A
	int _score;
public:
	//�R���X�g���N�^
	Ship();
	//�t�@�C����ǂݍ���
	int ReadDataBMP(const char* fileName, int index, vec2 defaultPos, float defaultRotate);
	//�v���C���[�̏������֐�
	int Initialize(const char* fileName, int index, vec2 defaultPos, float defaultRotate);
	static int AllInitialize();
	//Ship�̓�������͂���֐�
	void Input(bool turnLeft, bool turnRight, bool acceleration, bool attack);
	//�U���̏���
	void Attack();
	//�@�̂���񂳂���֐�
	void Turn();
	//�X�V����֐�
	void Update() override;
	static void AllUpdate();
	//�`��֐�
	void Draw() override;
	static void AllDraw();
	//�ʒu�̃Q�b�^�ƃZ�b�^
	vec2& GetPosition() { return _pos; }
	void SetPosition(vec2& pos) { _pos = pos; }

	//�����̃Q�b�^�ƃZ�b�^
	vec2& GetSpeed() { return _speed; }
	void SetSpeed(vec2& speed) { _speed = speed; }

	//�p�x�̃Q�b�^�ƃZ�b�^
	float GetRotate() const { return _rotate; }
	void SetRotate(float rotate) { _rotate = rotate; }

	//�X�R�A�̃Q�b�^�ƃZ�b�^
	int GetScore() const { return _score; }
	void SetScore(int score) { _score = score; }

	//���ꂽ���ǂ������肷��t���O
	bool _isDead;
	//�����̏���
	void GenerateExplosion();
	//Ship�����Z�b�g����֐�
	void Reset();
	//�L�[�̏�Ԃ��i�[����z��
	bool _keys[MAX_SHIP_KEY];
	//�L�[�����łɉ�����Ă��邩�𔻒肷��
	bool _lastKeys[MAX_SHIP_KEY];
};//class Ship

//�O������ϐ���ǂݍ���
extern Ship gShips[MAX_INDEX_SHIP];

