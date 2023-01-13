#pragma once
#include<cstdio>
//���ƌ^���ς̃��X�g���g����悤�ɂ���
#include<cstdarg>
#include"glut.h"
#include"glm/glm.hpp"
#include"Color.h"
using namespace glm;


//glut�ŏo�͂����t�H���g�̃T�C�Y��119.05
#define FONT_DEFAULT_SIZE       119.05f
//�s�Ԃ̃X�y�[�X�@glut�ł�33.33�ŏo�͂���� g p q y�Ȃǉ��ɂ͂ݏo���\���̂��镶�����l������
//#define FONT_DEFAULT_LINE_SPACE 33.33f
#define FONT_DEFAULT_THICKNESS  104.0f
#define MY_RGB 3
//�t�H���g��`
#define FONT GLUT_STROKE_MONO_ROMAN


////�t�H���g�̎��
//enum
//{
//	//�������l�߂ĕ\�������
//	FONT_FONT_ROMAN,
//	//���������Ԋu�ŕ\�������
//	FONT_FONT_MONO_ROMAN,
//	FONT_FONT_MAX,
//};


static vec2 _sizeXY = { FONT_DEFAULT_THICKNESS,FONT_DEFAULT_SIZE };
//�t�H���g�̈ʒu
static vec2 _pos;
//���s�Ɏg�p����֐�
static vec2 _originPos;
//�f�t�H���g�̃T�C�Y��100.0
static float _size = FONT_DEFAULT_SIZE;
static unsigned char _color[MY_RGB] = { 0xff,0xff,0xff };
//�t�H���g�̑����͈̔͂�0.5�`10
static float _thickness = 1;
//�E�B���h�E�̃T�C�Y�Ƀt�H���g�̃T�C�Y����������
static vec2 _screenSize = { 256,256 };

void FontInitialize(float width, float height);
void FontBegin();
void FontEnd();

//�t�H���g�̐ݒ�
//void FontSetFont(int font);
/*
	�g�p��
	FontSetFont(FONT_FONT_ROMAN);
	Text2D(0, 0, color.White, FONT_DEFAULT_SIZE/2, FontGetThicknessMax(), "SUGINO\nNORIHIRO");
*/

//�t�H���g�̈ʒu
void FontSetPosition(float x, float y);
void FontSetPosition(vec2 const& pos);

void FontScreenSize(float width, float height);

//�t�H���g�̃T�C�Y
float FontGetSize();
vec2 FontGetXYSize();
//�g�p�� size = FontGetLineSize();
//float FontGetLineSize();
//void  FontSetSize(float size);
void  FontSetXYSize(vec2 const& sizeXY);
void  FontSetXYSize(float width, float height);

//�t�H���g�̑���
float FontGetThicknessMin();
float FontGetThicknessMax();

/*
	���悢�����Ƒ���
	 FONT_DEFAULT_SIZE/2, FontGetThicknessMax()/2
*/

float FontGetThickness(int charactor);
/*
	��ʒ��S�̕������x���W
	x = (windowSize.x - FontGetLength((unsigned char*)str)) / 2; //������̒��S�̍��W���擾����
*/
float FontGetLength(const unsigned char* str);
float FontGetLength(const char* str);
void  FontSetThickness(float thickness);

void FontColor(unsigned char r, unsigned char g, unsigned char b);
void FontColor(unsigned char* color);

void FontDraw(const char* charactor, ...);
/*
	�g�p��
	FontBegin();
	{
		FontSetPosition(0, 0);
		FontSetSize(8);
		FontColor(color.Red);
		//�t�H���g��`�悷��
		FontDraw("HELLO");
	}
	FontEnd();

*/


//�e�L�X�g��\��������֐�
//Text2D(float X���W, float Y���W, unsigned char* �F, vec2 �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, vec2 sizeXY, const char* charactor, ...);

//Text2D(float X���W, float Y���W, unsigned char* �F, vec2 �����̃T�C�Y, float �����̑���, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, vec2 sizeXY, float thickness, const char* charactor, ...);

//Text2D(float X���W, float Y���W, unsigned char* �F, float �����̑���, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, float thickness, const char* charactor, ...);

//Text2D(float X���W, float Y���W, unsigned char* �F, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, const char* charactor, ...);

//Text2D(float X���W, float Y���W, unsigned char* �F, float �����̑���, const char* ������, ...)
//void Text2D(float posX, float posY, unsigned char* color, float thickness, const char* charactor, ...);

//Text2D(float X���W, float Y���W, vec2 �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, vec2 sizeXY, const char* charactor, ...);

//Text2D(float X���W, float Y���W, float �����̑���, const char* ������, ...)
//void Text2D(float posX, float posY, float thickness, const char* charactor, ...);

//Text2D(float X���W, float Y���W,const char* ������, ...)
void Text2D(float posX, float posY, const char* charactor, ...);

//class Font
//{
//public:
//	
//
//public:
//	//Font();
//	void FontBegin();
//	void FontEnd();
//	void FontSetPosition(float x, float y);
//	float FontGetSize();
//	void FontSetSize(float size);
//	void FontColor(unsigned char r, unsigned char g, unsigned char b);
//	void FontDraw(const char* charactor, ...);
//};

