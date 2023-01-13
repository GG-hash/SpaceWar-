#pragma once
#include"glut.h"
#include"glm\glm.hpp"
using namespace glm;
#define MY_RGB 3
#pragma warning(suppress : 5208)



//色の定義
struct Color {
	unsigned char Red[MY_RGB] = { 0xff,0,0 };
	unsigned char Green[MY_RGB] = { 0,0xff,0 };
	unsigned char Blue[MY_RGB] = { 0,0,0xff };
	unsigned char White[MY_RGB] = { 0xff,0xff,0xff };
	unsigned char LightGray[MY_RGB] = { 0xc0,0xc0,0xc0 };
	unsigned char LightBlue[MY_RGB] = { 0,0xff,0xff };
	unsigned char Gray[MY_RGB] = { 0x80,0x80,0x80 };
	unsigned char Ocher[MY_RGB] = { 0x80,0x80,0 };
	unsigned char Dark_Pink[MY_RGB] = { 0xff,0,0xff };
	unsigned char Blue_Green[MY_RGB] = { 0,0x80,0x80 };
	unsigned char Purple[MY_RGB] = { 0x80,0,0x80 };
	unsigned char Brown[MY_RGB] = { 0x80,0,0 };
	unsigned char Black[MY_RGB] = { 0,0,0 };
	unsigned char Yellow[MY_RGB] = { 0xff,0xff,0 };
};

typedef struct Colorub {
	GLubyte Red[MY_RGB] = { 0xff,0,0 };
	GLubyte Green[MY_RGB] = { 0,0xff,0 };
	GLubyte Blue[MY_RGB] = { 0,0,0xff };
	GLubyte White[MY_RGB] = { 0xff,0xff,0xff };
	GLubyte LightGray[MY_RGB] = { 0xc0,0xc0,0xc0 };
	GLubyte LightBlue[MY_RGB] = { 0,0xff,0xff };
	GLubyte Gray[MY_RGB] = { 0x80,0x80,0x80 };
	GLubyte Ocher[MY_RGB] = { 0x80,0x80,0 };
	GLubyte Dark_Pink[MY_RGB] = { 0xff,0,0xff };
	GLubyte Blue_Green[MY_RGB] = { 0,0x80,0x80 };
	GLubyte Purple[MY_RGB] = { 0x80,0,0x80 };
	GLubyte Brown[MY_RGB] = { 0x80,0,0 };
	GLubyte Black[MY_RGB] = { 0,0,0 };
	GLubyte Yellow[MY_RGB] = { 0xff,0xff,0 };
}Colorub;


//位置によって色を変更する関数
void SetColorWithPosition(vec2 const& pos);