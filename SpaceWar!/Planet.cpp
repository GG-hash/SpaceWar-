//#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include "Planet.h"
#include"glut.h"
#include"glm/glm.hpp"
using namespace glm;

//�O���[�o���ȃC���X�^���X
Planet gPlanet;

void Planet::Update()
{
}//void Planet::Update()


void Planet::Draw()
{
	//�����_���Ŋp�x�����߂�
	float randRot = M_PI * 2.0f * rand() / RAND_MAX;
	//�f���̑傫��
	float planetScale = 32.0f * rand() / RAND_MAX;

	vec2 vec[] = {
		vec2(-sin(randRot), cos(randRot)) * planetScale,
		vec2(sin(randRot),-cos(randRot)) * planetScale
	};

	glVertexPointer(2, GL_FLOAT, 0, vec);
	glDrawArrays(GL_LINES, 0, sizeof(vec) / sizeof(vec2));
}//void Planet::Draw()

