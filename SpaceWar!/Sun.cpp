//#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include "Sun.h"
#include"glut.h"
#include"glm/glm.hpp"
using namespace glm;

//グローバルなインスタンス
Sun gSun;

void Sun::Update()
{
}//void Sun::Update()


void Sun::Draw()
{
	//ランダムで角度を求める
	float randRot = M_PI * 2.0f * rand() / RAND_MAX;
	//太陽の大きさ
	float sunScale = 32.0f * rand() / RAND_MAX;

	vec2 vec[] = {
		vec2(-sin(randRot), cos(randRot)) * sunScale,
		vec2(sin(randRot),-cos(randRot)) * sunScale
	};

	glVertexPointer(2, GL_FLOAT, 0, vec);
	glDrawArrays(GL_LINES, 0, sizeof(vec) / sizeof(vec2));
}//void Sun::Draw()

