#pragma once
#include<cstdio>
#include<Windows.h>
#include"glut.h"
#include"glm/glm.hpp"
#include"Color.h"
//#include <string_view>

using namespace std;
using namespace glm;



//BMPファイルからテクスチャを読み込む関数
//テクスチャの貼り付けは、Rectクラスで定義した四角形の表面に張り付ける
int TextureFromBMP(const char* fileName, unsigned char* colorKey = nullptr);
int TextureFromBMP(const char* fileName, unsigned char colorKeyR, unsigned char colorKeyG, unsigned char colorKeyB);
//画像のアルファのみの読み込み
int TextureAlphaFromBMP(const char* fileName, unsigned char* buffer);
//テクスチャの描画
void DrawTexture(vec2 const& pos, vec2 const& size, unsigned int texture, const GLubyte* color);

enum
{
	TEX_SHIP,
	TEX_SHOOT,
	TEX_EXPLOSION,
	TEX_MAX
};

typedef struct
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	GLuint texture;
}TEX;

void TexFromFile(const char* filename, int texNo);

//テクスチャを読み込む関数
void SetUpTexture(const char* fname, int texNo);

/*
*
* 使用例 main関数内
	//テクスチャの画像数の取得
	glGenTextures(6, g_texIDs);
	//テクスチャの読み込み
	SetUpTexture("dice1.bmp", 0);
	SetUpTexture("dice2.bmp", 1);
	SetUpTexture("dice3.bmp", 2);
	SetUpTexture("dice4.bmp", 3);
	SetUpTexture("dice5.bmp", 4);
	SetUpTexture("dice6.bmp", 5);
*/

//テスト用のテクスチャの設定
void SetTextureMode(unsigned char* pixcels);