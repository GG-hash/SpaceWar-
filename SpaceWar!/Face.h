#pragma once
#include"glut.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<Windows.h>

#define RadsToDegrees(radian) ((radian) *(180.0 /M_PI))
#define DegreesToRads(degrees)((degrees) * (M_PI /180.0))

//���W	X Y Z
//3������Ԃ�\���}�`
typedef struct
{
	double x, y, z;
}POINT3D;

//�X�N���[�����\���_
typedef struct
{
	double x, y;
}POINT2D;

//3�����x�N�g��
typedef struct
{
	double x, y, z;
}VECTOR3D;

//�F��\���\����
typedef struct
{
	double r, g, b;
}COLOR;

//������\���\����
typedef struct
{
	VECTOR3D dir;//���s�����̌����̕���
	COLOR c;//�����̐F
}LIGHT;

//������\���\����
typedef struct
{
	int n0, n1;
}LINE;

//�ʂ�\���\���� �ő�̒��_��4�܂őΉ�
typedef struct
{
	//���_�̔ԍ�
	int n0, n1, n2, n3;
	//COLOR c;
}FACE;

//�ő�̒��_�̐�
#define MAX_POINT 128
//�ő�̗Ő��̐�
#define MAX_LINE 100
//�ő�̖ʂ̐�
#define MAX_FACE 128


//���C���[�t���[���̏����i�[����ϐ�///////
//���_�̐�
static int np = 0;
//�ӂ̐�
static int nl = 0;
//�ʂ̐�
static int nf = 0;
//�t�@�C������ǂݍ��񂾍��W���i�[����z��
static POINT3D p[MAX_POINT] = {};

static FACE f[MAX_FACE] = {};
//////////////////////////////////////////


#define MAX_SLICE 1000
#define MAX_STACK 1000

//�o�x
static int slices = 0;
//�ܓx
static int stacks = 0;

//�l�p�`�̏��
static int quads[MAX_SLICE][MAX_STACK][3];

//�����̈ʒu
//float pos[4] = { -1.0, 1.0, 1.0, 0.0 };

//�ϊ��s��
//double m[4][4];

//�e�N�X�`����ID���i�[����z��
//#define MAX_TEX 10000
//unsigned int g_texIDs[MAX_TEX];

//���e�ϊ��̌��ʂ�POINT2D�^�ŕԂ��֐�
POINT2D Perspective(POINT3D p);

//�ʂ̃f�[�^��ǂݍ��ފ֐�(Ver. ������)
int ReadSurfaceTxtData(const char* fileName);

/*
	1�ӂ�100�̗����̂�.txt�f�[�^�̗�

	8			   ���_�̐�
	  0,    0,   0 ���_�̍��W x y z �ォ�珇��1 2 3 4 5 6 7 8�ƒ��_�̔ԍ�������U����
	  0,100.0,   0
  100.0,100.0,   0
  100.0,    0,   0
  100.0,    0, -100.0
  100.0,100.0, -100.0
	  0,100.0, -100.0
	  0,    0, -100.0

	6             �ʂ̐�
	0, 3, 2, 1    ���_�̔ԍ������іʂ�`�悷��
	7, 6, 5, 4
	1, 2, 5, 6
	0, 7, 4, 3
	3, 4, 5, 2
	7, 0, 1, 6


*/



//���s������ݒu����֐�
void ParallelLightSource(float x, float y, float z);

//���f���̐F���w�肷��֐�
void SetColorWithLight(float r, float g, float b);

//3�����x�N�g�����󂯎��A�P�ʃx�N�g���ŕԂ��֐�
VECTOR3D Normalize(VECTOR3D n);

//�P�ʖ@���x�N�g����Ԃ��֐�
VECTOR3D Normal(FACE face);

//�ʂ̕`��
void DrawFace(FACE face, float r, float g, float b);

////�`����s���R�[���o�b�N
// �g�p��
//void myDisplay()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�`����e�̏���
//	glColor3d(1.0, 1.0, 1.0); //�`��̐F�̐ݒ�(��)
//
//
//
//	glEnable(GL_LIGHTING);
//	//������L���ɂ���
//	glEnable(GL_LIGHT0);
//	//�����̈ʒu
//	//float pos[4] = {-1.0, 1.0, 1.0, 0.0};
//	glLightfv(GL_LIGHT0, GL_POSITION, pos);
//
//
//	//�����̐F�̎w��
//	float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 }; //�g�U��
//	float light_specular[4] = { 0.1, 0.1, 0.1, 1.0 }; //���ʌ�
//	float light_ambient[4] = { 0.1, 0.1, 0.1, 1.0 }; //����
//
//
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//
//	//�e�N�X�`����`��o����悤�ɂ���
//	glEnable(GL_TEXTURE_2D);
//
//
//	glPushMatrix();
//	glShadeModel(GL_SMOOTH);
//	glRotated(-90, 0.0, 1.0, 0.0);
//	glRotated(angle, 1.0, 1.0, 1.0);
//	//DrawFace�֐�
//	for (int i = 0; i < nf; i++)
//	{
//		//�w��̃e�N�X�`���𒣂�t����
//		glBindTexture(GL_TEXTURE_2D, g_texIDs[i]);
//		DrawFace(f[i], 1, 1, 1);
//	}
//	glPopMatrix();
//
//	glDisable(GL_TEXTURE_2D);
//	
//
//	//�o�b�t�@��؂�ւ���
//	glutSwapBuffers();
//}
//

//�V�F�[�f�B���O���ꂽ����`�悷��֐�
//�w�i�̘f���ȂǂɎg��
void CircleWithShading(double radius, POINT3D center, double viewpoint, LIGHT light);

void mySolidSphere(float radius, int slices, int stacks);

