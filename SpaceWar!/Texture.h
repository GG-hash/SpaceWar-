#pragma once
#include<cstdio>
#include<Windows.h>
#include"glut.h"
#include"glm/glm.hpp"
#include"Color.h"
//#include <string_view>

using namespace std;
using namespace glm;



//BMP�t�@�C������e�N�X�`����ǂݍ��ފ֐�
//�e�N�X�`���̓\��t���́ARect�N���X�Œ�`�����l�p�`�̕\�ʂɒ���t����
int TextureFromBMP(const char* fileName, unsigned char* colorKey = nullptr);
int TextureFromBMP(const char* fileName, unsigned char colorKeyR, unsigned char colorKeyG, unsigned char colorKeyB);
//�摜�̃A���t�@�݂̂̓ǂݍ���
int TextureAlphaFromBMP(const char* fileName, unsigned char* buffer);
//�e�N�X�`���̕`��
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

//�e�N�X�`����ǂݍ��ފ֐�
void SetUpTexture(const char* fname, int texNo);

/*
*
* �g�p�� main�֐���
	//�e�N�X�`���̉摜���̎擾
	glGenTextures(6, g_texIDs);
	//�e�N�X�`���̓ǂݍ���
	SetUpTexture("dice1.bmp", 0);
	SetUpTexture("dice2.bmp", 1);
	SetUpTexture("dice3.bmp", 2);
	SetUpTexture("dice4.bmp", 3);
	SetUpTexture("dice5.bmp", 4);
	SetUpTexture("dice6.bmp", 5);
*/

//�e�X�g�p�̃e�N�X�`���̐ݒ�
void SetTextureMode(unsigned char* pixcels);