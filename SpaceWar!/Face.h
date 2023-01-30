#pragma once
#include"glut.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<Windows.h>

#define RadsToDegrees(radian) ((radian) *(180.0 /M_PI))
#define DegreesToRads(degrees)((degrees) * (M_PI /180.0))

//座標	X Y Z
//3次元空間を表す図形
typedef struct
{
	double x, y, z;
}POINT3D;

//スクリーン上を表す点
typedef struct
{
	double x, y;
}POINT2D;

//3次元ベクトル
typedef struct
{
	double x, y, z;
}VECTOR3D;

//色を表す構造体
typedef struct
{
	double r, g, b;
}COLOR;

//光源を表す構造体
typedef struct
{
	VECTOR3D dir;//平行光源の光線の方向
	COLOR c;//光源の色
}LIGHT;

//綾線を表す構造体
typedef struct
{
	int n0, n1;
}LINE;

//面を表す構造体 最大の頂点が4まで対応
typedef struct
{
	//頂点の番号
	int n0, n1, n2, n3;
	//COLOR c;
}FACE;

//最大の頂点の数
#define MAX_POINT 128
//最大の稜線の数
#define MAX_LINE 100
//最大の面の数
#define MAX_FACE 128


//ワイヤーフレームの情報を格納する変数///////
//頂点の数
static int np = 0;
//辺の数
static int nl = 0;
//面の数
static int nf = 0;
//ファイルから読み込んだ座標を格納する配列
static POINT3D p[MAX_POINT] = {};

static FACE f[MAX_FACE] = {};
//////////////////////////////////////////


#define MAX_SLICE 1000
#define MAX_STACK 1000

//経度
static int slices = 0;
//緯度
static int stacks = 0;

//四角形の情報
static int quads[MAX_SLICE][MAX_STACK][3];

//光源の位置
//float pos[4] = { -1.0, 1.0, 1.0, 0.0 };

//変換行列
//double m[4][4];

//テクスチャのIDを格納する配列
//#define MAX_TEX 10000
//unsigned int g_texIDs[MAX_TEX];

//投影変換の結果をPOINT2D型で返す関数
POINT2D Perspective(POINT3D p);

//面のデータを読み込む関数(Ver. 直方体)
int ReadSurfaceTxtData(const char* fileName);

/*
	1辺が100の立方体の.txtデータの例

	8			   頂点の数
	  0,    0,   0 頂点の座標 x y z 上から順に1 2 3 4 5 6 7 8と頂点の番号が割り振られる
	  0,100.0,   0
  100.0,100.0,   0
  100.0,    0,   0
  100.0,    0, -100.0
  100.0,100.0, -100.0
	  0,100.0, -100.0
	  0,    0, -100.0

	6             面の数
	0, 3, 2, 1    頂点の番号を結び面を描画する
	7, 6, 5, 4
	1, 2, 5, 6
	0, 7, 4, 3
	3, 4, 5, 2
	7, 0, 1, 6


*/



//平行光源を設置する関数
void ParallelLightSource(float x, float y, float z);

//モデルの色を指定する関数
void SetColorWithLight(float r, float g, float b);

//3次元ベクトルを受け取り、単位ベクトルで返す関数
VECTOR3D Normalize(VECTOR3D n);

//単位法線ベクトルを返す関数
VECTOR3D Normal(FACE face);

//面の描画
void DrawFace(FACE face, float r, float g, float b);

////描画を行うコールバック
// 使用例
//void myDisplay()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//描画内容の消去
//	glColor3d(1.0, 1.0, 1.0); //描画の色の設定(白)
//
//
//
//	glEnable(GL_LIGHTING);
//	//光源を有効にする
//	glEnable(GL_LIGHT0);
//	//光源の位置
//	//float pos[4] = {-1.0, 1.0, 1.0, 0.0};
//	glLightfv(GL_LIGHT0, GL_POSITION, pos);
//
//
//	//光源の色の指定
//	float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 }; //拡散光
//	float light_specular[4] = { 0.1, 0.1, 0.1, 1.0 }; //鏡面光
//	float light_ambient[4] = { 0.1, 0.1, 0.1, 1.0 }; //環境光
//
//
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//
//	//テクスチャを描画出来るようにする
//	glEnable(GL_TEXTURE_2D);
//
//
//	glPushMatrix();
//	glShadeModel(GL_SMOOTH);
//	glRotated(-90, 0.0, 1.0, 0.0);
//	glRotated(angle, 1.0, 1.0, 1.0);
//	//DrawFace関数
//	for (int i = 0; i < nf; i++)
//	{
//		//指定のテクスチャを張り付ける
//		glBindTexture(GL_TEXTURE_2D, g_texIDs[i]);
//		DrawFace(f[i], 1, 1, 1);
//	}
//	glPopMatrix();
//
//	glDisable(GL_TEXTURE_2D);
//	
//
//	//バッファを切り替える
//	glutSwapBuffers();
//}
//

//シェーディングされた球を描画する関数
//背景の惑星などに使う
void CircleWithShading(double radius, POINT3D center, double viewpoint, LIGHT light);

void mySolidSphere(float radius, int slices, int stacks);

