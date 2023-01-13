//#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include "Sun.h"
#include"glut.h"
#include"glm/glm.hpp"
using namespace glm;

//�O���[�o���ȃC���X�^���X
Sun gSun;

void Sun::Update()
{
}//void Sun::Update()


void Sun::Draw()
{
	//�����_���Ŋp�x�����߂�
	float randRot = M_PI * 2.0f * rand() / RAND_MAX;
	//���z�̑傫��
	float sunScale = 32.0f * rand() / RAND_MAX;

	vec2 vec[] = {
		vec2(-sin(randRot), cos(randRot)) * sunScale,
		vec2(sin(randRot),-cos(randRot)) * sunScale
	};

	glVertexPointer(2, GL_FLOAT, 0, vec);
	glDrawArrays(GL_LINES, 0, sizeof(vec) / sizeof(vec2));
}//void Sun::Draw()

