#pragma once
#include "Actor.h"
#include"glm/glm.hpp"
#include<vector>
using namespace std;
using namespace glm;

//�w�i�̐��̍ő�l
#define MAX_STAR     128
//�������߂�����
#define TINCLE_CYCLE 2

class MainBackGround :public Actor
{
private:
	//���̈ʒu���i�[����z��
	vec2 _points[MAX_STAR];
public:
	//�R���X�g���N�^
	MainBackGround();
	//����������֐�
	int Initialize();
	//�X�V����֐�
	void Update() override;
	//�`�悷��֐�
	void Draw() override;

};//class MainBackGround :public Actor

//�O���[�o���ȃC���X�^���X
extern MainBackGround gMainBG;
