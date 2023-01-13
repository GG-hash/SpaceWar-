#pragma once
#include<cstdio>
//個数と型が可変のリストを使えるようにする
#include<cstdarg>
#include"glut.h"
#include"glm/glm.hpp"
#include"Color.h"
using namespace glm;


//glutで出力されるフォントのサイズが119.05
#define FONT_DEFAULT_SIZE       119.05f
//行間のスペース　glutでは33.33で出力される g p q yなど下にはみ出す可能性のある文字を考慮する
//#define FONT_DEFAULT_LINE_SPACE 33.33f
#define FONT_DEFAULT_THICKNESS  104.0f
#define MY_RGB 3
//フォント定義
#define FONT GLUT_STROKE_MONO_ROMAN


////フォントの種類
//enum
//{
//	//文字が詰めて表示される
//	FONT_FONT_ROMAN,
//	//文字が等間隔で表示される
//	FONT_FONT_MONO_ROMAN,
//	FONT_FONT_MAX,
//};


static vec2 _sizeXY = { FONT_DEFAULT_THICKNESS,FONT_DEFAULT_SIZE };
//フォントの位置
static vec2 _pos;
//改行に使用する関数
static vec2 _originPos;
//デフォルトのサイズは100.0
static float _size = FONT_DEFAULT_SIZE;
static unsigned char _color[MY_RGB] = { 0xff,0xff,0xff };
//フォントの太さの範囲は0.5～10
static float _thickness = 1;
//ウィンドウのサイズにフォントのサイズを持たせる
static vec2 _screenSize = { 256,256 };

void FontInitialize(float width, float height);
void FontBegin();
void FontEnd();

//フォントの設定
//void FontSetFont(int font);
/*
	使用例
	FontSetFont(FONT_FONT_ROMAN);
	Text2D(0, 0, color.White, FONT_DEFAULT_SIZE/2, FontGetThicknessMax(), "SUGINO\nNORIHIRO");
*/

//フォントの位置
void FontSetPosition(float x, float y);
void FontSetPosition(vec2 const& pos);

void FontScreenSize(float width, float height);

//フォントのサイズ
float FontGetSize();
vec2 FontGetXYSize();
//使用例 size = FontGetLineSize();
//float FontGetLineSize();
//void  FontSetSize(float size);
void  FontSetXYSize(vec2 const& sizeXY);
void  FontSetXYSize(float width, float height);

//フォントの太さ
float FontGetThicknessMin();
float FontGetThicknessMax();

/*
	程よい高さと太さ
	 FONT_DEFAULT_SIZE/2, FontGetThicknessMax()/2
*/

float FontGetThickness(int charactor);
/*
	画面中心の文字列のx座標
	x = (windowSize.x - FontGetLength((unsigned char*)str)) / 2; //文字列の中心の座標を取得する
*/
float FontGetLength(const unsigned char* str);
float FontGetLength(const char* str);
void  FontSetThickness(float thickness);

void FontColor(unsigned char r, unsigned char g, unsigned char b);
void FontColor(unsigned char* color);

void FontDraw(const char* charactor, ...);
/*
	使用例
	FontBegin();
	{
		FontSetPosition(0, 0);
		FontSetSize(8);
		FontColor(color.Red);
		//フォントを描画する
		FontDraw("HELLO");
	}
	FontEnd();

*/


//テキストを表示させる関数
//Text2D(float X座標, float Y座標, unsigned char* 色, vec2 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, vec2 sizeXY, const char* charactor, ...);

//Text2D(float X座標, float Y座標, unsigned char* 色, vec2 文字のサイズ, float 文字の太さ, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, vec2 sizeXY, float thickness, const char* charactor, ...);

//Text2D(float X座標, float Y座標, unsigned char* 色, float 文字の太さ, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, float thickness, const char* charactor, ...);

//Text2D(float X座標, float Y座標, unsigned char* 色, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, const char* charactor, ...);

//Text2D(float X座標, float Y座標, unsigned char* 色, float 文字の太さ, const char* 文字列, ...)
//void Text2D(float posX, float posY, unsigned char* color, float thickness, const char* charactor, ...);

//Text2D(float X座標, float Y座標, vec2 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, vec2 sizeXY, const char* charactor, ...);

//Text2D(float X座標, float Y座標, float 文字の太さ, const char* 文字列, ...)
//void Text2D(float posX, float posY, float thickness, const char* charactor, ...);

//Text2D(float X座標, float Y座標,const char* 文字列, ...)
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

