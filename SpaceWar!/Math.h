#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include"glut.h"
#include"glm/glm.hpp"
#include"TwoVector.h"
#include"ThreeVector.h"
using namespace glm;

//angleを -M_PI < angle < M_PI へと修正する
float FixRadianAngle(float angle);





